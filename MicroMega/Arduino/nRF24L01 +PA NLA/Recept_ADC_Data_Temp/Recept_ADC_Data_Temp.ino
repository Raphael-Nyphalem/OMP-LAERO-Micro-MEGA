#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel

uint16_t data_out_CH0;
uint16_t data_out_CH1;
uint16_t data_out_CH2;
uint16_t data_out_CH3;
uint16_t data_out_CH4;
uint16_t data_out_CH5;
uint16_t data_out_CH6;
uint16_t data_out_CH7;
uint16_t data_out_CH8;
uint16_t data_out_CH9;

char Temp[7];

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  //Serial.println("Récepteur NRF24L01");
  //Serial.println("");
  Serial.println("SETUP");

  // Partie NRF24
  radio.begin();                      // Initialisation du module NRF24
  radio.openReadingPipe(0, adresse);  // Ouverture du tunnel en LECTURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.startListening();             // Démarrage de l'écoute du NRF24 (signifiant qu'on va recevoir, et non émettre quoi que ce soit, ici)
}

void loop() {
  // On vérifie à chaque boucle si un message est arrivé
  if (radio.available()) {

    //Data Capteurs
    //Charge le tableau dans Temp
    delay(110);
    radio.read(&data_out_CH0, sizeof(data_out_CH0));
    delay(110);
    radio.read(&data_out_CH1, sizeof(data_out_CH1));
    delay(110);
    radio.read(&data_out_CH2, sizeof(data_out_CH2));
    delay(110);
    radio.read(&data_out_CH3, sizeof(data_out_CH3));
    delay(110);
    radio.read(&data_out_CH4, sizeof(data_out_CH4));
    delay(110);
    radio.read(&data_out_CH5, sizeof(data_out_CH5));
    delay(110);
    radio.read(&data_out_CH6, sizeof(data_out_CH6));
    delay(110);
    radio.read(&data_out_CH7, sizeof(data_out_CH7));
    delay(110);
    radio.read(&data_out_CH8, sizeof(data_out_CH8));
    delay(110);
    radio.read(&data_out_CH9, sizeof(data_out_CH9));
    delay(110);
    radio.read(&Temp, sizeof(Temp));
    delay(110);
    
    // Affichage :
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH0);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH1);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH2);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH3);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH4);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH5);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH6);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH7);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH8);
    Serial.print('B'); //=========================== ADC_OUT GAZ
    Serial.print(data_out_CH9);
    
    Serial.print('T'); //=========================== Label Temperature
    for (int i = 0; i < sizeof(Temp); i++) {
      Serial.print(Temp[i]);
    }

    Serial.println("");
    

  }
}
