#include <SPI.h>

#define CS 10
#define EOC 9  //End Of Conversion


// Fonction d'initialisation de ADC pour 1èr valeur (ici data_out est ignoré)
void init_ADC(byte data_IN_8b) {

  byte data_out_1_ADC;
  byte data_out_2_ADC;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
  digitalWrite(CS, LOW);
  data_out_1_ADC = SPI.transfer(data_IN_8b);   // envoie des 8 bits d'input data register + reception 8 premiers bits de Data OUT
  data_out_2_ADC = SPI.transfer(B00000000);   // Pading -> bits ignore + reception 8 derniers bits de Data OUT
  SPI.endTransaction();
  digitalWrite(CS, HIGH);
}

// Récupère la valeur de la convertion précédente et envoie une nouvelle requête pour la lecture suivante
uint16_t ADC_ReadWrite(byte data_IN_8b) {

  uint16_t data_out_ADC;
  byte data_out_1_ADC;
  byte data_out_2_ADC;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
  digitalWrite(CS, LOW);
  data_out_1_ADC = SPI.transfer(data_IN_8b);   // envoie des 8 bits d'input data register + reception 8 premiers bits de Data OUT
  data_out_2_ADC = SPI.transfer(B00000000);   // Pading -> bits ignore + reception 8 derniers bits de Data_OUT
  SPI.endTransaction();
  digitalWrite(CS, HIGH);

  data_out_ADC = (data_out_1_ADC << 8) | data_out_2_ADC;  //Reconstruction de Data_OUT (16 bits)
  data_out_ADC = data_out_ADC >> 4;                       //Suppression des 4 zéros de fin

  return data_out_ADC;
}

//Convertion du résultat en mV (Ici utile pour debug, MAIS à faire sous Matlab)
float Conv_Data (uint16_t Data_OUT) {
  float resu = Data_OUT * (1.52 / 4096);
  return resu;
}

//********************************** SETUP **********************************//
void setup() {
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  pinMode(EOC, INPUT);

  SPI.begin();
  digitalWrite(CS, HIGH);

  init_ADC(B00001100);  //Requête de la première data (CH0)
}


//********************************** LOOP **********************************//
void loop() {

  uint16_t data_out;
  float tension_out;

  //============== ADC CH0-CH8  ==============//
  for (int i = 0 ; i < 9; i++) {

    Serial.print("//============== ADC CH"); Serial.print(i); Serial.println(" ==============//");
    byte adr_bit = i << 4;
    byte info_bit = B1100;
    byte byte_ADC = adr_bit | info_bit; //construction et réasemblage de Data_IN

    data_out = ADC_ReadWrite(byte_ADC);
    tension_out = Conv_Data(data_out);

    Serial.print("data_out : ");
    Serial.print(data_out, BIN); Serial.print(" "); Serial.println(data_out);
    Serial.print("Convertion : ");
    Serial.print(tension_out); Serial.print(" "); Serial.println("mV");
    Serial.println("");
  }

  //============== ADC CH9  ==============//
  Serial.println("//============== ADC CH9 ==============//");
  data_out = ADC_ReadWrite(B00001100); //Récupère data de la conv précédente + requête data CH0
  tension_out = Conv_Data(data_out);

  Serial.print("data_out : ");
  Serial.print(data_out, BIN); Serial.print(" "); Serial.println(data_out);
  Serial.println("");
  Serial.print("Convertion : ");
  Serial.print(tension_out); Serial.print(" "); Serial.println("mV");
  Serial.println("");

  Serial.println("//*****************************************************************************************************//");
}
