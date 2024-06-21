#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel

uint16_t data_outADC1_CH0;  //Gaz ADC data
uint16_t data_out_1;
uint16_t data_out_2;
uint16_t data_out_3;
uint16_t data_out_4;
uint16_t data_outADC1_CH5;
uint16_t data_outADC1_CH6;
uint16_t data_outADC1_CH7;
uint16_t data_outADC1_CH8;

uint16_t data_outADC2_CH0;  //Gaz ADC data
uint16_t data_outADC2_CH1;
uint16_t data_outADC2_CH2;
uint16_t data_outADC2_CH3;
uint16_t data_outADC2_CH4;
uint16_t data_outADC2_CH5;
uint16_t data_outADC2_CH6;
uint16_t data_outADC2_CH7;
uint16_t data_outADC2_CH8;
//uint16_t data_outADC2_CH9;

char Temp[7];           //Arduino sensors data
char Hum[7];
char Pres[7];
char Alt[7];

char UTC[9];            //GPS data
char Longitude[10];
char Latitude[11];
char AltitudeGPS[6];

//Tableaux de Data 

char Cpt_tab[sizeof(Temp)+sizeof(Hum)+sizeof(Pres)];//+sizeof(Alt)];

uint16_t ADC1_Tab[9]={data_outADC1_CH0,data_out_1,data_out_2,data_out_3,data_out_4,data_outADC1_CH5,data_outADC1_CH6,data_outADC1_CH7,data_outADC1_CH8};
uint16_t ADC2_Tab[9]={data_outADC2_CH0,data_outADC2_CH1,data_outADC2_CH2,data_outADC2_CH3,data_outADC2_CH4,data_outADC2_CH5,data_outADC2_CH6,data_outADC2_CH7,data_outADC2_CH8};

char GPS_tab_pt1[2+sizeof(UTC)+sizeof(Longitude)+1];
char GPS_tab_pt2[2+sizeof(Latitude)+sizeof(AltitudeGPS)+1];

//Fonction Calcul Taille
int size_uint16_t(uint16_t d) {
  if ((d >= 0) && (d < 10)) {
    return 1;
  }
  if ((d >= 10) && (d < 100)) {
    return 2;
  }
  if ((d >= 100) && (d < 1000)) {
    return 3;
  }
  if ((d >= 1000) && (d < 10000)) {
    return 4;
  }
  if ((d >= 10000) && (d < 100000)) {
    return 5;
  }
  else {
    return 6;
  }
}

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
 
  // NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_HIGH);      // RF24_PA_MIN; RF24_PA_LOW; RF24_PA_HIGH; RF24_PA_MAX)Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // si un message est arrivé
  if (radio.available()) {
    
    
    //===== Arduino Capteurs =====//
    radio.read(&Cpt_tab, sizeof(Cpt_tab));                      //Arduino sensors data
    delay(100);

    //===== ADC1 =====//
    radio.read(&ADC1_Tab, sizeof(ADC1_Tab));    //Gaz ADC data
    delay(100);
    radio.read(&ADC2_Tab, sizeof(ADC2_Tab));
    delay(100);
    
    
    //===== GPS Data =====//
    radio.read(&GPS_tab_pt1, sizeof(GPS_tab_pt1));                        //GPS data
    delay(100);
    radio.read(&GPS_tab_pt2, sizeof(GPS_tab_pt2));                        //GPS data
    delay(100);

    //===== Affichage =====//

    Serial.print('B');
    Serial.print(ADC1_Tab[0]);
    Serial.print('B');
    Serial.print(ADC1_Tab[1]);
    Serial.print('B');
    Serial.print(ADC1_Tab[2]);
    Serial.print('B');
    Serial.print(ADC1_Tab[3]);
    Serial.print('B');
    Serial.print(ADC1_Tab[4]);
    Serial.print('B');
    Serial.print(ADC1_Tab[5]);
    Serial.print('B');
    Serial.print(ADC1_Tab[6]);
    Serial.print('B');
    Serial.print(ADC1_Tab[7]);
    Serial.print('B');
    Serial.print(ADC1_Tab[8]);
    //
    Serial.print('C');
    Serial.print(ADC2_Tab[0]);
    Serial.print('C');
    Serial.print(ADC2_Tab[1]);
    Serial.print('C');
    Serial.print(ADC2_Tab[2]);
    Serial.print('C');
    Serial.print(ADC2_Tab[3]);
    Serial.print('C');
    Serial.print(ADC2_Tab[4]);
    Serial.print('C');
    Serial.print(ADC2_Tab[5]);
    Serial.print('C');
    Serial.print(ADC2_Tab[6]);
    Serial.print('C');
    Serial.print(ADC2_Tab[7]);
    Serial.print('C');
    Serial.print(ADC2_Tab[8]);

    Serial.print(Cpt_tab);
    
    Serial.print(GPS_tab_pt1);
    Serial.print(GPS_tab_pt2);
    

 

    //Correct padding length
    int pad_size = 0;

    int LongLigne = (16 + size_uint16_t(ADC1_Tab[0]) + size_uint16_t(ADC1_Tab[1]) + size_uint16_t(ADC1_Tab[2]) + size_uint16_t(ADC1_Tab[3]) + size_uint16_t(ADC1_Tab[4]) 
                        + size_uint16_t(ADC1_Tab[5]) + size_uint16_t(ADC1_Tab[6]) + size_uint16_t(ADC1_Tab[7])+ size_uint16_t(ADC1_Tab[8])
                        + size_uint16_t(ADC2_Tab[0]) + size_uint16_t(ADC2_Tab[1]) + size_uint16_t(ADC2_Tab[2]) + size_uint16_t(ADC2_Tab[3]) + size_uint16_t(ADC2_Tab[4]) 
                        + size_uint16_t(ADC2_Tab[5]) + size_uint16_t(ADC2_Tab[6]) + size_uint16_t(ADC2_Tab[7])+ size_uint16_t(ADC2_Tab[8])
                        + strlen(Cpt_tab) + strlen(GPS_tab_pt1) + strlen(GPS_tab_pt2)+2);
    
    int padding = 150 - LongLigne;
    for (int i = 0; i < padding; i++) {
      Serial.print('F');
      pad_size += 1;
    }
    pad_size += LongLigne;


//    Serial.println("");
//    Serial.print("LongLigne+padding : ");
//    Serial.print(LongLigne + padding);
//    Serial.print(" ");
//    Serial.print("LongLigne : ");
//    Serial.print(LongLigne);
//    Serial.print(" ");
    
//    Serial.print("Temp : ");
//    Serial.print(Temp);
//    Serial.print(" ");
//    Serial.print("sizeof(Temp) : ");
//    Serial.print(sizeof(Temp));
//    Serial.print(" ");
//    Serial.print("strlen(Temp) : ");
//    Serial.print(strlen(Temp));
//    Serial.print(" ");
//
//    Serial.print("Hum : ");
//    Serial.print(Hum);
//    Serial.print(" ");
//    Serial.print("sizeof(Hum) : ");
//    Serial.print(sizeof(Hum));
//    Serial.print(" ");
//    Serial.print("strlen(Hum) : ");
//    Serial.print(strlen(Hum));
//    Serial.print(" ");

//    Serial.print("Latitude : ");
//    Serial.print(Latitude);
//    Serial.print(" ");
//    Serial.print("sizeof(Latitude) : ");
//    Serial.print(sizeof(Latitude));
//    Serial.print(" ");
//    Serial.print("strlen(Latitude) : ");
//    Serial.print(strlen(Latitude));
//    Serial.print(" ");

//    Serial.print("data_outADC2_CH0 : ");
//    Serial.print(data_outADC2_CH0);
//    Serial.print(" ");
//    Serial.print("size_uint16_t(data_outADC2_CH0) : ");
//    Serial.print(size_uint16_t(data_outADC2_CH0));
//    Serial.print(" ");


// Ancien test ....=====================================
    //    Serial.println("");
    //    Serial.print("pad_size : ");
    //    Serial.println(pad_size);
    //    Serial.print("sizeof(Temp) : ");
    //    Serial.println(sizeof(Temp));
    //    Serial.print("strlen(Temp) : ");
    //    Serial.println(strlen(Temp));
    //    Serial.print("CH0_size : ");
    //    Serial.println(size_uint16_t(data_outADC1_CH0));
    //    Serial.print("CH1_size : ");
    //    Serial.println(size_uint16_t(data_out_1));
    //    Serial.print("CH2_size : ");
    //    Serial.println(size_uint16_t(data_out_2));
    //    Serial.print("CH3_size : ");
    //    Serial.println(size_uint16_t(data_out_3));
    //    Serial.print("CH4_size : ");
    //    Serial.println(size_uint16_t(data_out_4));
    //    Serial.print("CH5_size : ");
    //    Serial.println(size_uint16_t(data_outADC1_CH5));
    //    Serial.print("CH6_size : ");
    //    Serial.println(size_uint16_t(data_outADC1_CH6));
    //    Serial.print("CH7_size : ");
    //    Serial.println(size_uint16_t(data_outADC1_CH7));
    //    Serial.print("CH8_size : ");
    //    Serial.println(size_uint16_t(data_outADC1_CH8));

    Serial.println("");


  }
}
