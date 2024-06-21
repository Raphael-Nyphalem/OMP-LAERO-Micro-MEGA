#include <SPI.h>

#define CS 10
#define EOC 9  //End Of Conversion

void setup() {
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  pinMode(EOC, INPUT);

  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2); //8Mhz
  digitalWrite(CS, HIGH);

}

void loop() {

  //============== ADC Channel  ==============//
  byte data_out_1_ADC;
  byte data_out_2_ADC;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW);
    data_out_1_ADC = SPI.transfer(B00001100);   // envoie des 8 bits d'input data register + reception 8 premiers bits de Data OUT
    data_out_2_ADC = SPI.transfer(B00000000);   // Pading -> bits ignore + reception 8 derniers bits de Data OUT
    SPI.endTransaction();
    digitalWrite(CS, HIGH);
    
  for (int i = 0 ; i < 10; i++) {
    // Data IN

    Serial.print("//============== ADC CH");Serial.print(i); Serial.println(" ==============//");
    
    byte adr_bit = i << 4;
    byte info_bit = B1100;
    byte byte_ADC = adr_bit | info_bit; 

    
    //byte byte_ADC = B00001100; //0000 1100
    byte padding = B00000000; // 0000 0000 -> padding

    Serial.print("Data IN CH");Serial.print(i); Serial.println(" :");
    Serial.println(byte_ADC, BIN);
    Serial.println(padding, BIN);

    SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW);
    data_out_1_ADC = SPI.transfer(byte_ADC);   // envoie des 8 bits d'input data register + reception 8 premiers bits de Data OUT
    data_out_2_ADC = SPI.transfer(padding);   // Pading -> bits ignore + reception 8 derniers bits de Data OUT
    SPI.endTransaction();
    digitalWrite(CS, HIGH);

    // Data OUT
    uint16_t data_out_ADC = (data_out_1_ADC << 8) | data_out_2_ADC;
    data_out_ADC = data_out_ADC >> 4;

    Serial.print("Data OUT CH");;Serial.print(i); Serial.println(" :");
    Serial.println(data_out_ADC, BIN);
    Serial.println(data_out_ADC);
    Serial.println();

    float resu1 = data_out_ADC *(1.52/4096);
    Serial.println("Convertion : ");
    Serial.println(resu1);
  }
}
