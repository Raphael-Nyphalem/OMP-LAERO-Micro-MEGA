#include "SD_pmodmicrosd.h"


String sd_filename;

void init_SD()
{
    pinMode(SD_CS, OUTPUT);
  while (!SD.begin(SD_CS))   // Initialisation carte SD
  {
    Serial.println(" * Carte absente * : Reste carte SD...");
    SD.begin(SD_CS);
  }
  Serial.println("Carte initialisee.");
  int int_name = 0;

  sd_filename+=String(int_name);
  sd_filename+=".txt";

  while (SD.exists(sd_filename)==1)
  {
    int_name++;
    sd_filename=String(int_name);
    sd_filename+=".txt";
    Serial.print(sd_filename);
    Serial.println(" existe");
  }
  Serial.print("Fichier de cette session: ");
  Serial.println(sd_filename);

  File fichier = SD.open(sd_filename, FILE_WRITE);
  fichier.println("id HH MM SS longitude latitude altitude adc_1_ch0_Temperature adc_1_ch1 adc_1_ch2 adc_1_ch3 adc_1_ch4 adc_1_ch5 adc_1_ch6 adc_1_ch7 adc_1_ch8 adc_2_ch0_Temperature adc_2_ch1 adc_2_ch2 adc_2_ch3 adc_2_ch4 adc_2_ch5 adc_2_ch6 adc_2_ch7 adc_2_ch8 temp hum pres temp_baro t_prog date");
  fichier.close();
}

void ecriture_sd(
                String sd_filename,
                uint32_t id,
                unsigned long *pgmTime,
                char temp[TAILLE_TEMP],
                char hum[TAILLE_HUM],
                char pres[TAILLE_PRES],
                char temp_baro[TAILLE_TEMP_BARO],
                donnee_GPS* donnee_GPS,
                donnee_Alphasense* adc1,
                donnee_Alphasense* adc2,
                char date[TAILLE_DATE] )
{
    //=============== SD ===============//
    File fichier = SD.open(sd_filename, FILE_WRITE);    //Ouvre le ficher de sauvgarde data.txt, IMPORTANT : penser à ajouter la date !!
    if (fichier){//Si fichier available

      //TRAME:
      // [ id | GPS: hh mm ss long lat alt | adc 1 | adc 2 | temp | hum | pres | temp_baro | tmp_pro ]
      fichier.print(id);
      fichier.print(" ");

      if (donnee_GPS->utc[0] == 'N') {
        fichier.print("Nan");//heure 
        fichier.print(" "); 
        fichier.print("Nan");//min 
        fichier.print(" "); 
        fichier.print("Nan");//seconde
        fichier.print(" ");
      }
      else {
  //      for (int k = 0; k < (sizeof(UTC)); k++) {
  //        fichier.print(UTC[k]);
  //      }
  //      fichier.print(" ");
        fichier.print(donnee_GPS->utc[0]);fichier.print(donnee_GPS->utc[1]);fichier.print(" "); //heure 
        fichier.print(donnee_GPS->utc[2]);fichier.print(donnee_GPS->utc[3]);fichier.print(" "); //min 
        fichier.print(donnee_GPS->utc[4]);fichier.print(donnee_GPS->utc[5]);fichier.print(" "); //seconde
      }

      if (donnee_GPS->longitude[0] == 'N') {
        fichier.print("Nan");
      }
      else {
        fichier.print(donnee_GPS->longitude);
      }
      fichier.print(" ");

      if (donnee_GPS->latitude[0] == 'N') {
        fichier.print("Nan");
      }
      else {
        for (int k = 0; k < (sizeof(donnee_GPS->latitude)); k++) {
          fichier.print(donnee_GPS->latitude[k]);
        }
      }
      fichier.print(" ");

      if (donnee_GPS->altitudeGPS[0] == 'N' || donnee_GPS->altitudeGPS[0] == '-') {
        fichier.print("Nan");
      }
      else {
        for (int k = 0; k < (sizeof(donnee_GPS->altitudeGPS)); k++) {
          fichier.print(donnee_GPS->altitudeGPS[k]);
        }
      }
      fichier.print(" ");

      //ADC1 ch0 to ch8
      fichier.print(adc1->data_out_ch0);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch1);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch2);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch3);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch4);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch5);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch6);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch7);
      fichier.print(" ");
      fichier.print(adc1->data_out_ch8);
      fichier.print(" ");

      // ADC2 ch0 to ch8
      fichier.print(adc2->data_out_ch0);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch1);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch2);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch3);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch4);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch5);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch6);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch7);
      fichier.print(" ");
      fichier.print(adc2->data_out_ch8);
      fichier.print(" ");

      
      // Capteurs
      fichier.print(temp);
      fichier.print(" ");

      fichier.print(hum);
      fichier.print(" ");

      fichier.print(pres);
      fichier.print(" ");

      fichier.print(temp_baro);
      fichier.print(" ");


      //temps du programme
      fichier.print(*pgmTime);
      fichier.print(" ");

      fichier.print(date);
      fichier.print(" ");

      // fichier.print(timeF->alphasens);
      // fichier.print(" ");

      // fichier.print(timeF->gps_read);
      // fichier.print(" ");

      // fichier.print(timeF->split);
      // fichier.print(" ");
      
      // fichier.print(timeF->temperature);
      // fichier.print(" ");
      // fichier.print(timeF->humidity);
      // fichier.print(" ");
      // fichier.print(timeF->barometre);
      // fichier.print(" ");

      //trame GGA lu
      // if (trameGGA->trame[0] == '\0')
      // {
      //   fichier.print("Nan");
      // }
      // else
      // {
      //   fichier.print(trameGGA->trame);
      // }

      fichier.println("");

      fichier.close();
      if(PRINT_MSG_SERIAL)
      {
        Serial.println("SD : * DataSave *");
        Serial.println("");
      }
    }
    else                            //Si ficher n'existe pas ou erreur faux contact
    {
      Serial.println("SD : * Carte SD non detecter *");
      while (!SD.begin(SD_CS))   // Initialisation carte SD
      {
        Serial.println("Tentative de reconnexion SD : * Reset de la carte SD... *");
        SD.begin(SD_CS);
        delay(100);
      }
    }
}
