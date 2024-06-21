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
char OrientationNS[1];
char Latitude[11];
char OrientationOE[1];
char AltitudeGPS[6];

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
  //Serial.println("Récepteur NRF24L01");
  //Serial.println("");
  //Serial.println("SETUP");

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_HIGH);      // RF24_PA_MIN; RF24_PA_LOW; RF24_PA_HIGH; RF24_PA_MAX)Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {

    //===== ADC1 =====/
    //delay(110);
    radio.read(&data_outADC1_CH0, sizeof(data_outADC1_CH0));    //Gaz ADC data
    delay(110);
    radio.read(&data_out_1, sizeof(data_out_1));
    delay(110);
    radio.read(&data_out_2, sizeof(data_out_2));
    delay(110);
    radio.read(&data_out_3, sizeof(data_out_3));
    delay(110);
    radio.read(&data_out_4, sizeof(data_out_4));
    delay(110);
    radio.read(&data_outADC1_CH5, sizeof(data_outADC1_CH5));
    delay(110);
    radio.read(&data_outADC1_CH6, sizeof(data_outADC1_CH6));
    delay(110);
    radio.read(&data_outADC1_CH7, sizeof(data_outADC1_CH7));
    delay(110);
    radio.read(&data_outADC1_CH8, sizeof(data_outADC1_CH8));
    delay(110);
    //===== ADC2 =====/
    delay(110);
    radio.read(&data_outADC2_CH0, sizeof(data_outADC2_CH0));    //Gaz ADC data
    delay(110);
    radio.read(&data_outADC2_CH1, sizeof(data_outADC2_CH1));
    delay(110);
    radio.read(&data_outADC2_CH2, sizeof(data_outADC2_CH2));
    delay(110);
    radio.read(&data_outADC2_CH3, sizeof(data_outADC2_CH3));
    delay(110);
    radio.read(&data_outADC2_CH4, sizeof(data_outADC2_CH4));
    delay(110);
    radio.read(&data_outADC2_CH5, sizeof(data_outADC2_CH5));
    delay(110);
    radio.read(&data_outADC2_CH6, sizeof(data_outADC2_CH6));
    delay(110);
    radio.read(&data_outADC2_CH7, sizeof(data_outADC2_CH7));
    delay(110);
    radio.read(&data_outADC2_CH8, sizeof(data_outADC2_CH8));
    delay(110);
    //===== Arduino Capteurs =====//
    radio.read(&Temp, sizeof(Temp));                      //Arduino sensors data
    delay(110);
    radio.read(&Hum, sizeof(Hum));
    delay(110);
    radio.read(&Pres, sizeof(Pres));
    delay(110);
    radio.read(&Alt, sizeof(Alt));
    delay(110);
    radio.read(&UTC, sizeof(UTC));                        //GPS data
    delay(110);
    radio.read(&Longitude, sizeof(Longitude));
    delay(110);
    radio.read(&OrientationNS, sizeof(OrientationNS));
    delay(110);
    radio.read(&Latitude, sizeof(Latitude));
    delay(110);
    radio.read(&OrientationOE, sizeof(OrientationOE));
    delay(110);
    radio.read(&AltitudeGPS, sizeof(AltitudeGPS));
    delay(110);

    // Affichage ADC1 :
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC1_CH0);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_1);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_2);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_3);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_4);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC1_CH5);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC1_CH6);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC1_CH7);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC1_CH8);

    // Affichage ADC2 :
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH0);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH1);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH2);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH3);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH4);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH5);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH6);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH7);
    Serial.print('C'); //=========================== ADC_OUT GAZ
    Serial.print(data_outADC2_CH8);

    Serial.print('T'); //=========================== Label Temperature
    for (int i = 0; i < sizeof(Temp); i++) {
      Serial.print(Temp[i]);
    }
    Serial.print('H'); //=========================== Label Humidité
    for (int i = 0; i < sizeof(Hum); i++) {
      Serial.print(Hum[i]);
    }
    Serial.print('P'); //=========================== Label Pression
    for (int i = 0; i < sizeof(Pres); i++) {
      Serial.print(Pres[i]);
    }
    Serial.print('A'); //=========================== Label Altitude
    for (int i = 0; i < sizeof(Alt); i++) {
      Serial.print(Alt[i]);
    }

    Serial.print('U'); //=========================== Label Temps UTC
    for (int i = 0; i < sizeof(UTC); i++) {
      Serial.print(UTC[i]);
    }
    Serial.print('L'); //=========================== Label Longitude
    for (int i = 0; i < sizeof(Longitude); i++) {
      Serial.print(Longitude[i]);
    }
    Serial.print('O'); //=========================== Label OrientationNS
    for (int i = 0; i < sizeof(OrientationNS); i++) {
      Serial.print(OrientationNS[i]);
    }
    Serial.print('L'); //=========================== Label Latitude
    for (int i = 0; i < sizeof(Latitude); i++) {
      Serial.print(Latitude[i]);
    }
    Serial.print('O'); //=========================== Label OrientationOE
    for (int i = 0; i < sizeof(OrientationOE); i++) {
      Serial.print(OrientationOE[i]);
    }
    Serial.print('A'); //=========================== Label AltitudeGPS
    for (int i = 0; i < sizeof(AltitudeGPS); i++) {
      Serial.print(AltitudeGPS[i]);
    }
    delay(100);

    //Correct padding length
    int pad_size = 0;

    int LongLigne = ( size_uint16_t(data_outADC1_CH0) + size_uint16_t(data_out_1) + size_uint16_t(data_out_2) + size_uint16_t(data_out_3) + size_uint16_t(data_out_4)
                      + size_uint16_t(data_outADC1_CH5) + size_uint16_t(data_outADC1_CH6) + size_uint16_t(data_outADC1_CH7) + size_uint16_t(data_outADC1_CH8) + size_uint16_t(data_outADC2_CH0) + size_uint16_t(data_outADC2_CH1) + size_uint16_t(data_outADC2_CH2) + size_uint16_t(data_outADC2_CH3) + size_uint16_t(data_outADC2_CH4)
                      + size_uint16_t(data_outADC2_CH5) + size_uint16_t(data_outADC2_CH6) + size_uint16_t(data_outADC2_CH7) + size_uint16_t(data_outADC2_CH8) + strlen(Temp)
                      + strlen(Hum) + strlen(Pres) + strlen(Alt) + sizeof(UTC) + sizeof(Longitude) + sizeof(OrientationNS) + sizeof(Latitude) + sizeof(OrientationOE)
                      + sizeof(AltitudeGPS) + 20);    //+ size_uint16_t(data_outADC2_CH9)

    int padding = 155 - LongLigne;
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
