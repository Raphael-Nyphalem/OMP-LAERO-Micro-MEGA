//***********************************
//*   Test RemoteFreenove           *
//*                                 *
//*   Modifier le 02/09/22          *
//*                                 *
//*   Arthur NICOLA                 *
//*                                 *
//***********************************
#include <SPI.h>
#include <RF24.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE1"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;    // Mise au format "byte array" du nom du tunnel


//Sorties Analogiques
int Jx = 3;
int Jy = 2;
int Jz = 7;
int POT1 = 0;
int POT2 = 1;

//Sorties Digitales 
int S1 = 4;  
int S2 = 3;
int S3 = 2;

//data Radio 

int data[6];


void setup() {
  
  //joystick
  Serial.begin(115200);
  pinMode(Jx, OUTPUT);
  pinMode(Jy, OUTPUT);
  
  //Potentiometer
  pinMode(POT1, OUTPUT);
  pinMode(POT2, OUTPUT);

  //Radio 
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" (-6 dBm) pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
}


void loop() {

  //joystick
  Serial.print("x : ");
  Serial.println(analogRead(Jx));
  Serial.println("");
  Serial.print("y : ");
  Serial.println(analogRead(Jy));
  Serial.println("");
  Serial.print("z : ");
  Serial.println(digitalRead(Jz));
  Serial.println("");

  //Potentiometer
  Serial.print("Potentiometer1 : ");
  Serial.println(analogRead(POT1));
  Serial.println("");
  
  Serial.print("Potentiometer2 : ");
  Serial.println(analogRead(POT2));
  Serial.println("");

  //Buttons/Switchs
  Serial.print("Button/Switch1 : ");
  Serial.println(digitalRead(S1));
  Serial.println("");
  
  Serial.print("Button/Switch2 : ");
  Serial.println(digitalRead(S2));
  Serial.println("");
  
  Serial.print("Button/Switch3 : ");
  Serial.println(digitalRead(S3));
  Serial.println("");

  // Stockage dans tableau data pour envoie radio
  data [0] = analogRead(Jx); 
  data [1] = analogRead(Jy);
  data [2] = digitalRead(Jz);
  data [3] = analogRead(POT1);
  data [4] = analogRead(POT2);
  data [5] = digitalRead(S1);
  

  //Radio 
  radio.write(&data, sizeof(data));
  
  delay(2000);
}
