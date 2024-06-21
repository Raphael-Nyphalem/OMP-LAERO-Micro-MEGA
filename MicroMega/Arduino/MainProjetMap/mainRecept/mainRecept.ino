#include "Data.h"
#include <ArduinoSTL.h>  //librairie map, math, string et autre... => STL
#include <map>
#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24

using namespace std;

//Radio
RF24 radio(pinCE, pinCSN);        // Instanciation du NRF24L01
const byte adresse[6] = tunnel;   // Mise au format "byte array" du nom du tunnel

//Data
MapData M1;
Humidity H1;
Temperature T1;
std::map <String, int> MapData::Data_map;

void setup() {
  Serial.begin(74880);
  //Radio
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
  //Data
  M1.beginData(); 
  Serial.println("Data initiale dans la Map :");
  //M1.afficher_map();
  Serial.println();
}

void loop() {

  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {
    Serial.println("Data available");
    radio.read(&M1, sizeof(M1));                        // Si un message vient d'arriver, on le charge dans la variable "M1"
    M1.afficher_map();     // … et on l'affiche sur le port série !
  }
  
  delay(3000);


}
