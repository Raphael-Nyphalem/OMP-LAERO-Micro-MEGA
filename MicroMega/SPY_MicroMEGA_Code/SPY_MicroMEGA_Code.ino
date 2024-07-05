#include "SPY_MicroMEGA_Code.h"
//asm volatile("jmp 0x00"); restart carte

#include "Termometre_DS18B20.h"
#include "Hygrometre_BMP388.h"
#include "Barometre_HTU21D-F.h"

#include "GPS_NEO-6M.h"
#include "Alphasense_A4.h"
#include "SD_pmodmicrosd.h"

#include "RFD_MODEM.h"
//#include "Radio_NRF24L01+PA.h"




void setup() {

  Serial.begin(115200);
  Serial.println("Début Setup/");

  //======== Temperature ========//
  init_termometre();

  //======== Humidity ========//
  init_hygrometre();

  //======== Barometre ========//
  init_barometre();

  //======== GPS ========//
  
  initGPS();

  //===== Alphasense ====//
  init_alphasense();

  //======== SD ========//
  init_SD();

  setupRadio();


  Serial.println("Fin Setup/");
}

//**************************************** LOOP Program ****************************************//
//**********************************************************************************************//
void loop() {
  static uint32_t id = 0;
  bool gps_buff_good_RMC = false;
  static bool flag_RMC = false;
  bool gps_buff_good_GGA = false;
  

  static unsigned long temps_passer = millis();
  unsigned long temp_ecoule =  millis() - temps_passer;

  static bool flag_gga = false;
  static bool flag_1Hz = false;

  static unsigned long t_gps_gga;

  static trameNMEA GPS_buff;
  static trameNMEA trameRMC;


  

  if (flag_gga==false)
  {
    t_gps_gga = millis();

  }

  if (lectureNMEA(&GPS_buff))
  {
    gps_buff_good_RMC = isRMC(&GPS_buff);
    gps_buff_good_GGA = isGGA(&GPS_buff);
  }

  if (gps_buff_good_RMC)
  {
    lecture_gps(&GPS_buff,&trameRMC);
    flag_RMC = true;
  }
  else if (gps_buff_good_GGA)
  {
    flush();
  }
  
  

  // gps_buff_good_GGA = lectureGGA(&GPS_buff);

  
  if (temp_ecoule >= 1005)
    {
      flag_1Hz = true;
      id++;
    }
  else 
  {
     if (gps_buff_good_GGA && flag_gga== false)
    {
      if(PRINT_MSG_SERIAL)
      {
      Serial.println("\nNMEA GGA");
      Serial.println(GPS_buff.trame);
      Serial.println(GPS_buff.taille);
      Serial.println("\n");
      }
      id++;
      flag_gga = true;
    }
  }
  
  if ((flag_1Hz==true) || (flag_gga == true ))//&& temp_ecoule > 990) engendre des problème d'id
  {
    
    temps_passer = millis();
    flag_1Hz = false;
    

    char temp[TAILLE_TEMP];
    char hum[TAILLE_HUM];
    char pres[TAILLE_PRES];
    char temp_baro[TAILLE_TEMP_BARO];
    char date[TAILLE_DATE];

    trameNMEA trameGGA;
    struct donnee_GPS donnee_GPS;
    

    struct donnee_Alphasense adc1;
    struct donnee_Alphasense adc2;
    char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO] = {0};
    
    unsigned long pgmTime = {0};
    unsigned long t_pres; 
    struct temps_fonction timeF;

    t_pres = millis();
    pgmTime = t_pres; //Temps depuis l'exécution du programme

    
    timeF.setupRadio = millis() - t_pres;
    t_pres += timeF.setupRadio;

    //=============== Temperature ===============//
    lecture_temp(temp);
    //=============== FIN température ===============//


    timeF.temperature = millis() - t_pres;
    t_pres += timeF.temperature;

    //=============== Humidity ===============//
    lecture_humidite(hum);
    //=============== FIN Humidity ===============//


    timeF.humidity = millis() - t_pres;
    t_pres += timeF.humidity;

    //=============== Barometre ===============//
    lecture_barometre(pres,temp_baro);  

  //=============== FIN Barometre ===============//


    timeF.barometre = millis() - t_pres;
    t_pres += timeF.barometre;


    //<<-------------<< Affichage Capteurs Data >>------------->>//
    if (PRINT_MSG_SERIAL)
    {
          
      Serial.print("Temp :  ");
      Serial.print(temp);
      Serial.print(" ");

      Serial.print("Hum :  ");
      Serial.print(hum);
      Serial.print(" ");

      Serial.print("Pres :  ");
      Serial.print(pres);
      Serial.print(" ");

      Serial.print("Temp_baro :  ");
      Serial.print(temp_baro);
      Serial.print(" ");

      //  Serial.print("Alt :  ");
      //  for (int i=0; i < sizeof(Alt); i++){
      //    Serial.print(Alt[i]);
      //  }
      Serial.println("");
    }

    //<<--------------------------------------------------->>//

    //=============== GPS ===============//
    timeF.gps_read =pgmTime - t_gps_gga;

    if (flag_gga == true)
    {
      lecture_gps(&GPS_buff,&trameGGA);
    }
    flag_gga = false;

    if (flag_RMC)
    {
      Serial.println("READ RMC");
      read_date_RMC(&trameRMC,date);
      flag_RMC = false;
    }
    


    split_trame_gga(&trameGGA,&donnee_GPS);


    timeF.split = millis() - t_pres;
    t_pres += timeF.split;

    //<<-------------<< Affichage GPS Data >>------------->>//
    if(PRINT_MSG_SERIAL)
    {
      Serial.print("date : ");
      for (int k = 0; k < (TAILLE_DATE); k++) {
        Serial.print(date[k]);
      }
      Serial.print(" ");
      Serial.print("UTC : ");
      for (int k = 0; k < (TAILLE_UTC); k++) {
        Serial.print(donnee_GPS.utc[k]);
      }
      Serial.print(" ");
      Serial.print("Longitude : ");
      for (int k = 0; k < (TAILLE_LONG); k++) {
        Serial.print(donnee_GPS.longitude[k]);
      }
      Serial.print(" ");
      Serial.print("Latitude : ");
      for (int k = 0; k < (TAILLE_LAT); k++) {
        Serial.print(donnee_GPS.latitude[k]);
      }
      Serial.print(" ");
      Serial.print("AltitudeGPS : ");
      for (int k = 0; k < (TAILLE_ALT ); k++) {
        Serial.print(donnee_GPS.altitudeGPS[k]);
      }
      Serial.println("");
    }
    //<<--------------------------------------------------->>//

    alphasens(&adc1,&adc2,tab_adc_brut_radio);

    timeF.alphasens = millis() - t_pres;
    t_pres += timeF.alphasens;

    
    /* //<<-------------<< TEST Affichage ADC Data Binaire>>------------->>//
    if(PRINT_MSG_SERIAL)
    {
      Serial.print("ADC1 Binaire : ");
      Serial.print(adc1.data_out_ch0); Serial.print(' ');
      Serial.print(adc1.data_out_ch1); Serial.print(' ');
      Serial.print(adc1.data_out_ch2); Serial.print(' ');
      Serial.print(adc1.data_out_ch3); Serial.print(' ');
      Serial.print(adc1.data_out_ch4); Serial.print(' ');
      Serial.print(adc1.data_out_ch5); Serial.print(' ');
      Serial.print(adc1.data_out_ch6); Serial.print(' ');
      Serial.print(adc1.data_out_ch7); Serial.print(' ');
      Serial.print(adc1.data_out_ch8); Serial.println(' ');

      Serial.print("ADC2 Binaire : ");
      Serial.print(adc2.data_out_ch0); Serial.print(' ');
      Serial.print(adc2.data_out_ch1); Serial.print(' ');
      Serial.print(adc2.data_out_ch2); Serial.print(' ');
      Serial.print(adc2.data_out_ch3); Serial.print(' ');
      Serial.print(adc2.data_out_ch4); Serial.print(' ');
      Serial.print(adc2.data_out_ch5); Serial.print(' ');
      Serial.print(adc2.data_out_ch6); Serial.print(' ');
      Serial.print(adc2.data_out_ch7); Serial.print(' ');
      Serial.print(adc2.data_out_ch8); Serial.println(' ');
      Serial.println("");
      //<<--------------------------------------------------->>//
    }
    */
  

    ecriture_sd(sd_filename,id,&pgmTime,temp, hum,pres,temp_baro,
                &donnee_GPS,&adc1,&adc2,date);
      uint16_t t_SD = millis() - t_pres;
      t_pres += t_SD;
  
    ecriture_radio(temp, hum, pres,&donnee_GPS,tab_adc_brut_radio);

      uint16_t t_radio = millis() - t_pres;
      t_pres += t_radio;
    
    //Serial.print("LOOP time : "); Serial.print(t_pres - pgmTime); Serial.println("ms");
    //<<----------------------------------------------<< Affichage des temps d'execuions >>---------------------------------------------->>// 
    if(PRINT_MSG_SERIAL)
    { 
      Serial.println(" ");
      Serial.print("ID : "); Serial.println(id);
      Serial.print("Programme time : "); Serial.print(pgmTime); Serial.println("ms");
      Serial.print("LOOP calcul time : "); Serial.print(t_pres - pgmTime); Serial.println("ms");
      Serial.print("SetupRadio time : "); Serial.print(timeF.setupRadio); Serial.println("ms");
      Serial.print("Temperature time : "); Serial.print(timeF.temperature); Serial.println("ms");
      Serial.print("Humidity time : "); Serial.print(timeF.humidity); Serial.println("ms");
      Serial.print("Barometre time : "); Serial.print(timeF.barometre); Serial.println("ms");
      Serial.print("GPS time : "); Serial.print(timeF.gps_read); Serial.println("ms");
      Serial.print("Split GPS time : "); Serial.print(timeF.split); Serial.println("ms");

      Serial.print("Acquisition_ADC1_ADC2 time : "); Serial.print(timeF.alphasens); Serial.println("ms");
      Serial.print("Radio Emission All Data time : "); Serial.print(t_radio); Serial.println("ms");
      
      Serial.print("Sauvgarde SD time : "); Serial.print(t_SD); Serial.println("ms");
      //<<--------------------------------------------------------------------------------------------------------------------------------->>//
      Serial.println(" ");
      
      Serial.print("temp_ecoule "); Serial.print(temp_ecoule); Serial.println("ms");
      Serial.println(">>================================================================================//");
    }
  }
}

/*
volatile char receivedChar;
volatile bool newData = false;
volatile bool toggleLed = false;

const int ledPin = 13; // Pin de la LED intégrée

void setup() {
  // Configurer la pin de la LED comme sortie

  // Configuration du Timer1 pour générer une interruption toutes les secondes
  TCCR1A = 0; // Désactiver la sortie PWM
  TCCR1B = 0; // Arrêter le timer
  TCNT1 = 0;  // Initialiser le compteur à 0
  OCR1A = 15624; // Régler la valeur de comparaison (1 seconde pour 16 MHz avec prescaler 1024)
  TCCR1B |= (1 << WGM12); // Mode CTC (Clear Timer on Compare Match)
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A); // Activer l'interruption de comparaison du Timer1

  // Configuration de Serial1 pour 9600 bauds avec interruptions sur réception
  unsigned int ubrr = 103; // Correspond à 9600 bauds pour un F_CPU de 16 MHz
  UBRR1H = (unsigned char)(ubrr >> 8);
  UBRR1L = (unsigned char)ubrr;
  UCSR1B = (1 << RXEN1) | (1 << RXCIE1); // Activer la réception et les interruptions sur réception
  UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // Configurer le format : 8 bits de données, 1 bit d'arrêt

  // Activer les interruptions globales
  sei();

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Interruptions de Timer1 et Serial1 configurées");
}

void loop() {
  if (newData) {
    Serial.print("Caractère reçu sur Serial1 : ");
    Serial.println(receivedChar);
    newData = false;
  }

  if (toggleLed) {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1); // Inverser l'état de la LED
    toggleLed = false;
  }
}

// Routine d'interruption de réception série pour Serial1
ISR(USART1_RX_vect) {
  receivedChar = UDR1; // Lire le caractère reçu de Serial1
  newData = true;      // Indiquer qu'un nouveau caractère a été reçu
}

// Routine d'interruption de comparaison du Timer1
ISR(TIMER1_COMPA_vect) {
  toggleLed = true; // Indiquer à la boucle principale de basculer la LED
}
*/