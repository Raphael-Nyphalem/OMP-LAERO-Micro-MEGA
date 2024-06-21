//***********************************
//*   Reception Data Remote         *
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

int data[6]; 
void setup() {
  
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, adresse);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  Serial.println("Pouet");
  if(radio.available()){

    radio.read(&data, sizeof(data));
    delay(10);

    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(data[2]);
    Serial.println(data[3]);
    Serial.println(data[4]);
    Serial.println(data[5]);
    
  }
    
}
