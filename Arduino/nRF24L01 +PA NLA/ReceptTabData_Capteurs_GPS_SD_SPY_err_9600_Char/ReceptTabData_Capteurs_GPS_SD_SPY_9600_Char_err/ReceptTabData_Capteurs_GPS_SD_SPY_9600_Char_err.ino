#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
float Tab[4];                     // Avec cette librairie, on est "limité" à 32 caractères par message <=> 32 octet

char Temp[7];
char Hum[7];
char Pres[7];
char Alt[7];

char UTC[9];
char Longitude[10];
char OrientationNS[1];
char Latitude[11];
char OrientationOE[1];
char AltitudeGPS[6];

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  //Serial.println("Récepteur NRF24L01");
  //Serial.println("");

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {

    //Tableau float data 
//    radio.read(&Tab, sizeof(Tab));                        //Charge le tableau reçu dans Tab 
//    delay(10);

    //Data Capteurs 
    radio.read(&Temp, sizeof(Temp));                        //Charge le tableau dans Temp
    delay(10);
    radio.read(&Hum, sizeof(Hum));                        //Charge le tableau dans Temp
    delay(10);
    radio.read(&Pres, sizeof(Pres));                        //Charge le tableau dans Temp
    delay(10);
    radio.read(&Alt, sizeof(Alt));                        //Charge le tableau dans Temp
    delay(10);

    //Data GPS
    radio.read(&UTC, sizeof(UTC));                        //Charge le tableau reçu dans UTC
    delay(10);
    radio.read(&Longitude, sizeof(Longitude));                        //Charge le tableau reçu dans Longitude
    delay(10);    
    radio.read(&OrientationNS, sizeof(OrientationNS));                        //Charge le tableau  reçu dans OrientationNS
    delay(10);    
    radio.read(&Latitude, sizeof(Latitude));                        //Charge le tableau reçu dans Latitude
    delay(10);    
    radio.read(&OrientationOE, sizeof(OrientationOE));                        //Charge le tableau reçu dans OrientationOE
    delay(10);    
    radio.read(&AltitudeGPS, sizeof(AltitudeGPS));                        //Charge le tableau reçu dans AltitudeGPS
    delay(10);
    

    Serial.print('T'); //=========================== Label Temperature
    for(int i=0; i<sizeof(Temp); i++){
      Serial.print(Temp[i]);
    }

    Serial.print('H'); //=========================== Label Humidité
    for(int i=0; i<sizeof(Hum); i++){
      Serial.print(Hum[i]);
    }

    Serial.print('P'); //=========================== Label Pression
    for(int i=0; i<sizeof(Pres); i++){
      Serial.print(Pres[i]);
    }

    Serial.print('A'); //=========================== Label Altitude
    for(int i=0; i<sizeof(Alt); i++){
      Serial.print(Alt[i]);
    }

    Serial.print('U'); //=========================== Label Temps UTC
    for(int i=0; i<sizeof(UTC); i++){
      Serial.print(UTC[i]);
    }
    
    Serial.print('L'); //=========================== Label Longitude
    for(int i=0; i<sizeof(Longitude); i++){
      Serial.print(Longitude[i]);
    }

    Serial.print('O'); //=========================== Label OrientationNS
    for(int i=0; i<sizeof(OrientationNS); i++){
      Serial.print(OrientationNS[i]);
    }

    Serial.print('L'); //=========================== Label Latitude
    for(int i=0; i<sizeof(Latitude); i++){
      Serial.print(Latitude[i]);
    }

    Serial.print('O'); //=========================== Label OrientationOE
    for(int i=0; i<sizeof(OrientationOE); i++){
      Serial.print(OrientationOE[i]);
    }

    Serial.print('A'); //=========================== Label AltitudeGPS
    for(int i=0; i<sizeof(AltitudeGPS); i++){
      Serial.print(AltitudeGPS[i]);
    }
    
    int pad_size = 0;
    int LongLingne = (sizeof(Temp)+sizeof(Hum)+sizeof(Pres)+sizeof(Alt)+sizeof(UTC)+sizeof(Longitude)+sizeof(OrientationNS)+sizeof(Latitude)+sizeof(OrientationOE)+sizeof(AltitudeGPS)+10);
    int padding = 80 - LongLingne;
    for(int i = 0; i < padding; i++){
    Serial.print('F');
      pad_size += 1;
    }
    pad_size += LongLingne;
//    Serial.println("");
//    Serial.print("strlen(Temp) : ");
//    Serial.println(strlen(Temp));
//    Serial.print("sizeof(Temp) : ");
//    Serial.println(sizeof(Temp));
//    Serial.print("LongLingne : ");
//    Serial.println(LongLingne);
//    Serial.print("pad_size : ");
//    Serial.println(pad_size);
    Serial.println("");

  }
}
