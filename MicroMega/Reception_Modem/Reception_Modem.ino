#include "RFD_MODEM_RECEPTION.h"
       // On définit le "nom de tunnel" (5 caractères) à travers lequel on va recevoir les données de l'émetteur



const uint8_t TAILLE_TEMP = 7;
const uint8_t TAILLE_PRES = 7;
const uint8_t TAILLE_ALT = 5;
const uint8_t TAILLE_MESURE_ALPHASENCE = 2;

const uint16_t TEMPS_RESEPTION_LONG = 5000; // 5000 = 5s

const uint8_t MAX_TAB_RADIO = 32;

const uint8_t MAX_CHAR_T_ECOULE = 5;
const uint8_t MAX_CHAR_DATA_OUT = 4;


char Temp[TAILLE_TEMP]; 
char Pres[TAILLE_PRES];

char qualiteConnection;

char AltitudeGPS[TAILLE_ALT];

void setup() {
  // Initialisation du port série (pour afficher les infos reçues, sur le "Moniteur Série" de l'IDE Arduino)
  Serial.begin(115200);
  Serial.println("Initialisation ARDUINO Reception");
 
  // NRF24
  setupRadio();

  Serial.println("FIN initialisation ARDUINO Reception");
  Serial.println("Attente réception de trame");
}

void loop() {
  static unsigned long t_pres = millis();
  static char tab[MAX_TRAME_RECEPTION]={0};
  static bool flag_temps_recption_long = false;

  unsigned long t_actuel = millis();
  uint16_t t_ecoule = t_actuel-t_pres;

  if (t_ecoule > TEMPS_RESEPTION_LONG && !flag_temps_recption_long)
  {
    Serial.println("Erreur Perte signal Radio");
    flag_temps_recption_long = true;
  }
  
  

  if(lecture(tab)){
    String trameEmition = "";
    flag_temps_recption_long = false;
    // char trameEmition2[64];
    // for (uint8_t i = 0; i < MAX_TRAME_RECEPTION; i++)
    //   {
    //     Serial.write(tab[i]);
    //   }
    // Serial.println(' ');

    
    
    static char char_t_ecoule[MAX_CHAR_T_ECOULE];

    uint16_t adc1_ch1;
    uint16_t adc1_ch2;
    uint16_t adc1_ch3;
    uint16_t adc1_ch4;
    uint16_t adc1_ch5;
    uint16_t adc1_ch6;
    uint16_t adc1_ch7;
    uint16_t adc1_ch8;

    uint16_t adc2_ch1;
    uint16_t adc2_ch2;
    uint16_t adc2_ch3;
    uint16_t adc2_ch4;
    uint16_t adc2_ch5;
    uint16_t adc2_ch6;
    uint16_t adc2_ch7;
    uint16_t adc2_ch8;

    itoa(t_ecoule,char_t_ecoule,10);
    t_pres = t_actuel;
    
   
    
    
    uint8_t idn_trame_lctr = 0;

    bool test_indice_1 = (tab[0] & 0xF0) == 0x10;
    if ( test_indice_1 )
    {
      trameEmition+='#';
      
      trameEmition += '1';

      trameEmition+=':';


      trameEmition += String(t_ecoule);
      trameEmition+=':';

      //indice
      char test = tab[0];
      if((test & 0x0F) == 0x0F)//test si la connection GPS est bonne
      {
        trameEmition+= '3';
      }
      else if((test & 0x0C) == 0x0C)//test si la connection GPS est ok (au moins UTC et altitude)
      {
        trameEmition+= '2';
      }
      else if((test & 0x08) == 0x08)//test si la connection GPS est bof (UTC)
      {
        trameEmition+= '1';
      }
      else if((test & 0x0F) == 0x00)//test si la connection GPS est nul
      {
        trameEmition+= '0';
      }
      else
      {
        trameEmition+= '0';
      }

      trameEmition+=':';

      idn_trame_lctr+=TAILLE_INDICE;

      //temperature
      for (uint8_t i = 0; i < TAILLE_TEMP; i++)
      {
        trameEmition+=String(tab[i+idn_trame_lctr]);
      }
      idn_trame_lctr+=TAILLE_TEMP;

      trameEmition+=':';

      //pression
      for (uint8_t i = 0; i < TAILLE_PRES; i++)
      {
        trameEmition+=String(tab[i+idn_trame_lctr]);
      }
      idn_trame_lctr+=TAILLE_PRES;

      trameEmition+=':';

      //altitude
      for (uint8_t i = 0; i < TAILLE_ALT; i++)
      {
        trameEmition+=String(tab[i+idn_trame_lctr]);
      }
      idn_trame_lctr+=TAILLE_ALT;

      adc1_ch1 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc1_ch2 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc1_ch3 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc1_ch4 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc1_ch5 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc1_ch6 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc1_ch7 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc1_ch8 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc2_ch1 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc2_ch2 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc2_ch3 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc2_ch4 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc2_ch5 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc2_ch6 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      adc2_ch7 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;
      adc2_ch8 = data_out(tab,idn_trame_lctr);
      idn_trame_lctr+=TAILLE_MESURE_ALPHASENCE;

      volatile uint16_t tab_1_adc[16]={ adc1_ch1, adc1_ch2,
                              adc1_ch3, adc1_ch4, 
                              adc1_ch5, adc1_ch6,
                              adc1_ch7, adc1_ch8,
                              adc2_ch1, adc2_ch2,
                              adc2_ch3, adc2_ch4,
                              adc2_ch5, adc2_ch6,
                              adc2_ch7, adc2_ch8
                              };
      
      for (uint8_t idx = 0; idx < 16; idx++)
      {
        trameEmition+=':';
        trameEmition+=String(tab_1_adc[idx]);
      }

      //affichage:
      Serial.print(trameEmition);
      Serial.println('!');

      }


  }
}

uint16_t data_out(char tab[MAX_TAB_RADIO],uint8_t idx_trm_lctr)
{
  uint16_t val_data_out =0;
  byte data_1 = tab[idx_trm_lctr];
  byte data_2 = tab[idx_trm_lctr+1];

  val_data_out =  (data_1 << 8) | data_2;
  val_data_out = val_data_out >> 4;
  return val_data_out;
}
