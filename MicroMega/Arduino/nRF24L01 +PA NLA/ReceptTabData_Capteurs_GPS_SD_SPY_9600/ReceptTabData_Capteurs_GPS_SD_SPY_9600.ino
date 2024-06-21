#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
float Tab[4];                     // Avec cette librairie, on est "limité" à 32 caractères par message <=> 32 octet
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
    radio.read(&Tab, sizeof(Tab));                        //Charge le tableau dans Tab 
    delay(10);
    radio.read(&UTC, sizeof(UTC));                        //Charge le tableau dans Tab
    delay(10);
    radio.read(&Longitude, sizeof(Longitude));                        //Charge le tableau dans Tab
    delay(10);
    radio.read(&OrientationNS, sizeof(OrientationNS));                        //Charge le tableau dans Tab
    delay(10);
    radio.read(&Latitude, sizeof(Latitude));                        //Charge le tableau dans Tab
    delay(10);
    radio.read(&OrientationOE, sizeof(OrientationOE));                        //Charge le tableau dans Tab
    delay(10);
    radio.read(&AltitudeGPS, sizeof(AltitudeGPS));                        //Charge le tableau dans Tab
    delay(10);

    Serial.print('T'); //=========================== Label Temperature

    //    Serial.print("Temperature : ");
    Serial.print(Tab[0]);

    Serial.print('H'); //=========================== Label Humidité

    //    Serial.print("Humidité : ");
    Serial.print(Tab[1]);

    Serial.print('P'); //=========================== Label Pression

    //    Serial.print("Pression : ");
    Serial.print(Tab[2]);

    Serial.print('A'); //=========================== Label Altitude

    //    Serial.print("Altitude approx. : ");
    Serial.print(Tab[3]);

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
    Serial.println("");
  }
}
