// Inclure les librairies suivantes
#include <OneWire.h>
#include <DallasTemperature.h>

// Protocole de donnée OneWire branché sur la pin 3 de l'Arduino
#define ONE_WIRE_BUS 3 

OneWire oneWire(ONE_WIRE_BUS);
// Capteur de température Dallas en OneWire
DallasTemperature sensors(&oneWire);

void setup(void)
{
Serial.begin(9600); // Initialisation du port de communication série
Serial.println("Température digitale DS18B20 sur Pin 3 de l'Arduino"); // Affiche ce message sur le moniteur série
sensors.begin();
}

void loop(void)
{ 
// Aquisition de valeur de la température
sensors.requestTemperatures();
Serial.print("La température est: "); 
Serial.println(sensors.getTempCByIndex(0));  // Affiche de la température
delay(1000);  // Valeur rafraîchi toute les 1 seconde
}
