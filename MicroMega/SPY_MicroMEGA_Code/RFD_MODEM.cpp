#include "RFD_MODEM.h"

#define radio Serial3

void setupRadio(void) {
    radio.begin(57600,SERIAL_8N1);
    radio.write(START_COMMANDE_AT,3);
    _attente();
    // delay(1000);
    sendATCommand("ATS2=188");//188 vitesse dans l'air 188 000 bit/s
    
    sendATCommand("ATS3=169");//NETID id pour la communication

    sendATCommand("ATS4=10");//25mW

    sendATCommand("ATS11=1");//1% duty cycle
    sendATCommand("AT&W");
    sendATCommand(REBOOT);//stop commande
    
    delay(1000);
}


void sendATCommand(String command) {
  radio.println(command);
  unsigned long tempPres = millis();
  delay(50);
  while (true) {
    if (radio.available())
    {
        String reponse = radio.readString();
        Serial.print("Commande: ");
        Serial.print(command);
        Serial.print("| Reponse: ");
        Serial.println(reponse);
        break;
    }
    uint32_t test  = (millis() - tempPres );
    if (test > 3000)
    {
      Serial.print(test);
      tempPres = millis();
        Serial.print(" | Commande: ");
        Serial.print(command);
        Serial.println(" | Pas de Reponse");
        break;
    }
  }
}

void _attente()
{
  unsigned long tempPres = millis();
   while (true) {
    if (radio.available())
    {
        String response = radio.readString();
        Serial.print("Response: ");
        Serial.println(response);
        break;
    }
    uint32_t test  = (millis() - tempPres );
    if (test > 3000)
    {
      Serial.print(test);
      tempPres = millis();
        Serial.println("Pas de Reponce");
        break;
    }
  }

}

void ecriture_radio(
                    char temp[TAILLE_TEMP],
                    char hum[TAILLE_HUM],
                    char pres[TAILLE_PRES],
                    donnee_GPS *donnee_GPS,
                    char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO]
                    )
{
  // Déclaration des variables locales
  register char tabRadio[MAXTRAME] = {0};

  uint8_t decalage = 0;

  tabRadio[decalage]=SIGNE_DEBUT_TRAME;//0
  decalage+=TAILLE_SIGNE;
  tabRadio[decalage]=SIGNE_DEBUT_TRAME;//1
  decalage+=TAILLE_SIGNE;
  // Construction de la première trame
  //indice type trame + qualité GPS

  char indice_qualite = 0x10 | donnee_GPS->qualite_signal;
  tabRadio[decalage]=indice_qualite;//2
  decalage+=TAILLE_INDICE;

  //température
  !PRINT_MSG_SERIAL ? : Serial.print("\nTemp: ") ;
  for (uint8_t i = 0; i < TAILLE_TEMP; i++)
  {
    tabRadio[i+decalage]=temp[i];
    !PRINT_MSG_SERIAL ? : Serial.print(temp[i]);
  }
  decalage+=TAILLE_TEMP;

  //pression
  !PRINT_MSG_SERIAL ? : Serial.print("\nPres: ");
  for (uint8_t i = 0; i < TAILLE_PRES; i++)
  {
    tabRadio[i+decalage]=pres[i];
    !PRINT_MSG_SERIAL ? : Serial.print(pres[i]);
  }
  decalage+=TAILLE_PRES;
  
  //altitude
  if (donnee_GPS->altitudeGPS[0] == 'N' || donnee_GPS->altitudeGPS[0] == '-')
  {
      for (uint8_t i = 0; i < TAILLE_ALT; i++)
    {
      tabRadio[i+decalage]='X'; //lorsque on a pas de valeur on remplace par des 'X' dans la Trame
    }
  }
  else
  {
      for (uint8_t i = 0; i < TAILLE_ALT; i++)
    {
      
      tabRadio[i+decalage]=donnee_GPS->altitudeGPS[i];
    }
  }
  decalage+=TAILLE_ALT;
  uint8_t a = 0;

  //Serial.print(decalage);
  for (uint8_t i = 0; i < TAILLE_TAB_DATA_ADC_RADIO; i++)
  {
    tabRadio[i+decalage] = tab_adc_brut_radio[i];
  }
  decalage+=TAILLE_TAB_DATA_ADC_RADIO;

  tabRadio[decalage]=SIGNE_FIN_TRAME;//0
  decalage+=TAILLE_SIGNE;
  tabRadio[decalage]=SIGNE_FIN_TRAME;//1
  decalage+=TAILLE_SIGNE;

  // Affichage des trames si le mode debug est activé
  if(PRINT_MSG_SERIAL)
  {
    Serial.print("\ntab_adc_brut_radio: ");
    for (uint8_t i = 0; i < TAILLE_TAB_DATA_ADC_RADIO; i++)
    {
      Serial.print(tab_adc_brut_radio[i]);
    }
    Serial.println(' ');

    Serial.print("\nTrame: ");
    for (uint8_t i = 0; i < sizeof(tabRadio); i++)
    {
      Serial.print(tabRadio[i]);
    }
    Serial.println(' ');

    Serial.print("Decalage: ");
    Serial.println(decalage);
  }

  //envoie trame tabRadio [type de trame, qualiter gps, temperature, pression; altitude gps, ADC x 4]
  //envoie trame tabRadio2 [type de trame, qualiter gps, ADC x 12]
  
  // Envoi des trames via le module NRF24L01+
  radio.write(tabRadio,decalage);


}