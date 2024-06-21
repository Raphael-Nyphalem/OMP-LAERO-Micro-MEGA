#include "Hygrometre_BMP388.h"

HTU21D htu;

void init_hygrometre()
{
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
  }

}

void lecture_humidite(char hum[TAILLE_HUM])
{
  float Data;
  String strFloat; 
  htu.readSensor();
  if (isnan(htu.getHumidity()) || isnan(htu.getTemperature_C())) { // Check si lecture failed
    Serial.println("HTU21D sensor read failure!");
  }

  Data = htu.getHumidity();
  // for (int i = 0; i < TAILLE_HUM; i++) {
  //   Serial.print(hum[i]);
  //     } 
  if (Data == -1.00) {   //Si erreur capteur valeur : -1.00
    strFloat = "Nan";
    strFloat.toCharArray(hum, TAILLE_HUM);
  }
  else { 
        strFloat = String(Data,3);
    strFloat.toCharArray(hum, TAILLE_HUM);
  }
}