#include "Termometre_DS18B20.h"

OneWire oneWire(ONE_WIRE_BUS); ///< Initialisation du bus OneWire
DallasTemperature TempSensors(&oneWire);///< Initialisation des capteurs de température Dallas


void init_termometre()
{
  TempSensors.begin();
}


void lecture_temp(char temp[TAILLE_TEMP])
{
  float Data;
  String strFloat; 
  TempSensors.requestTemperatures();
    Data = TempSensors.getTempCByIndex(0);     
    if (Data == -127.0) {   //Si erreur capteur valeur : -127.0 
      strFloat = "Nan";
      strFloat.toCharArray(temp, TAILLE_TEMP+1);
    }
    else {
      strFloat = String(Data,3);
      strFloat.toCharArray(temp, TAILLE_TEMP+1);
    }
}
