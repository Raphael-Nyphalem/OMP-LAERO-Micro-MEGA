#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel
float Tab[4];                     // Avec cette librairie, on est "limité" à 32 caractères par message <=> 32 octet

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
    delay(500);
    
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
  }
}
