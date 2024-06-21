#include "RFD_MODEM_RECEPTION.h"


// RFD_MODEM::RFD_MODEM(self,uint8_t pinRX,uint8_t pinTX)
// {
//     SoftwareSerial self.radio(pinRX, pinTX)
// }

// RFD_MODEM::~RFD_MODEM()
// {
// }

SoftwareSerial radio(pinRX,pinTX);

void setupRadio(void) {
    Serial.println("Setup Radio (30s)");
    radio.begin(57600);

    radio.write(START_COMMANDE_AT,3);
    attente();
    delay(1000);
    sendATCommand("ATS2=188");//188 vitesse dans l'air 188 000 bit/s
    sendATCommand("ATS3="+NETID);//NETID id pour la communication

    sendATCommand("ATS4=10");//25mW

    sendATCommand("ATS11=1");//1% duty cycle
    sendATCommand("AT&W");
    sendATCommand(REBOOT);//stop commande
    Serial.println("FIN Setup Radio");
    delay(300);
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
    if (test > 700)
    {
      // Serial.print(test);
      tempPres = millis();
        Serial.print(" | Commande: ");
        Serial.print(command);
        Serial.println(" | Pas de Reponse");
        break;
    }
  }
}
void attente()
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
    if (test > 700)
    {
      tempPres = millis();
      Serial.println("Pas de Réponse");
      break;
    }
  }

}

bool lecture(char tab[MAX_TRAME_RECEPTION]){
  bool tabPret = false;

  static bool flagDebut = false;
  static bool flagDetecteSigneDebut = false;
  static bool flagDetecteSigneFin = false;

  static uint8_t index = 0;

  if (radio.available()>0)
  {
    char lu = radio.read();

    if (index < MAX_TRAME_RECEPTION)
    {
      tab[index]=lu; 
      index++;
    }
    else  //sécuriter si on est full
    {
      index =0;
      del_tableau(tab);
    }

    if (detection(lu,'#',&flagDetecteSigneDebut))
    {
      flagDetecteSigneDebut = false;
      flagDebut = true;
      del_tableau(tab);
      index = 0;
    }

    if (detection(lu,'$',&flagDetecteSigneFin))
    {
      tabPret = true;
    }
    
    // if (DEBUG)
    // {
    //   // Serial.print(lu);
    //   Serial.print("lu = ");
    //   Serial.println(lu);
    //   Serial.print("index = ");
    //   Serial.println(index);
    //   Serial.print("tableau : ");
    //   for (uint8_t i = 0; i < index; i++)
    //   {
    //     Serial.write(tab[i]);
    //   }
    //   Serial.println(" ");
    // }

    
  }
  return tabPret;
}

void del_tableau(char tab[MAX_TRAME_RECEPTION])
{
  for (int i = 0; i < MAX_TRAME_RECEPTION; i++)
  {
    tab[i]='0';
  }
}

bool detection(char charLu, char signe, bool *flag_1_lu)
{
  bool retourne = false;

  if ((charLu == signe) && (*flag_1_lu == false))
  {
    *flag_1_lu = true;
  }
  else
  {
    if ((charLu == signe) && *flag_1_lu)
    {
      *flag_1_lu = false;
      retourne = true;
    }
    else
    {
      *flag_1_lu = false;
    }
  }
  // if (DEBUG)
  //   {
  //     Serial.print("char lu = ");
  //     Serial.println(charLu);
  //     Serial.print("signe = ");
  //     Serial.println(signe);
  //     Serial.print("flag = ");
  //     Serial.println(*flag_1_lu);
  //   }
  return retourne;
}
