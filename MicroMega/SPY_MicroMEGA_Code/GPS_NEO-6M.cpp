#include "GPS_NEO-6M.h"

void initGPS() {
  gps_port.setTimeout(480); // set time max to wait for serial GPS data in ms : 480
  gps_port.begin(9600,SERIAL_8N1);
  // send configuration data in UBX protocol
  for (byte i = 0; i < sizeof(UBLOX_INIT); i++) {
    gps_port.write(UBLOX_INIT[i]);
  }
  delay (100);
  gps_port.print("$PUBX,41,1,0003,0001,115200,0*1E\r\n");
  delay (100);
  gps_port.begin(newGPSBaud);
}


void lecture_gps(trameNMEA *GPSBuffer,trameNMEA *trameGGA)
{
  //=============== GPS ===============//
      trameGGA->taille = GPSBuffer->taille;
      for (int i = 0; i < trameGGA->taille; i++)
      {
        trameGGA->trame[i]=GPSBuffer->trame[i];
      }
      GPSBuffer->taille =0;

    //<<-------------<< Affichage GPS TrameGGA >>------------->>//
    if(PRINT_MSG_SERIAL)
    {
      Serial.print("trame :  ");
      Serial.print(trameGGA->trame);
      Serial.println("<== FIN ==>");
    }
    //<<--------------------------------------------------->>//

}

void split_trame_gga(trameNMEA *trameGGA,struct donnee_GPS *donnee_GPS)
{
  
    //=============== Si Trame GGA vide  ===============//
    char radio_qualite_gps = 0x00;
    /*
    radio_qualite_gps est initialisée à 0x00 (tous les bits à 0). 
    Au fur et à mesure que les données sont extraites de la trame, des bits spécifiques sont mis à 1 
    pour indiquer que certaines informations sont disponibles.

    Bit 0 (0x01) : Disponibilité de la latitude.
    Bit 1 (0x02) : Disponibilité de la longitude.
    Bit 2 (0x04) : Disponibilité de l'altitude GPS.
    Bit 3 (0x08) : Disponibilité de l'heure UTC.
    
    */

      donnee_GPS->utc[0] = 'N';
      donnee_GPS->utc[1] = 'a';
      donnee_GPS->utc[2] = 'n';
      donnee_GPS->utc[3] = '\0';
      //
      donnee_GPS->longitude[0] = 'N';
      donnee_GPS->longitude[1] = 'a';
      donnee_GPS->longitude[2] = 'n';
      donnee_GPS->longitude[3] = '\0';
      //
      donnee_GPS->latitude[0] = 'N';
      donnee_GPS->latitude[1] = 'a';
      donnee_GPS->latitude[2] = 'n';
      donnee_GPS->latitude[3] = '\0';
      //
      donnee_GPS->altitudeGPS[0] = 'N';
      donnee_GPS->altitudeGPS[1] = 'a';
      donnee_GPS->altitudeGPS[2] = 'n';
      donnee_GPS->altitudeGPS[3] = '\0';
    
    //=============== Split Trame GGA ===============//
      
      //>> Séparation des données de la trameGGA :
      int c_cpt = 0;
      int index = 0;
      int Aux = 0;
      bool fin_data = true;
      int total_size = 0;
      

      while (index < (trameGGA->taille) && fin_data) {

        if (trameGGA->trame[index] == ',') {
          c_cpt++ ;
          if (c_cpt == 1 || c_cpt == 4 || c_cpt == 6 || c_cpt == 7 || c_cpt == 8 || c_cpt == 9 ) {
            Aux = index + 1;
            index++;
          }

          // >> Time UTC
          if (c_cpt == 2) {
            if (index - Aux > 0) {         //Si data non vide
              int UTC_size = index - Aux;
              for (int i = 0; i < UTC_size; i++) {
                donnee_GPS->utc[i] = trameGGA->trame[Aux];
                Aux++;
              }
              Aux = index + 1;
              index++;
              total_size = total_size + UTC_size;
              radio_qualite_gps = radio_qualite_gps | 0x08;
            }
            else {
              donnee_GPS->utc[0] = 'N';
              donnee_GPS->utc[1] = 'a';
              donnee_GPS->utc[2] = 'n';
              donnee_GPS->utc[3] = '\0';
              for (int i = 0; i < sizeof(donnee_GPS->utc); i++) {
                Aux++;
              }
              Aux = index + 1;
              index++;

            }
          }

          //>>  Longitude
          if (c_cpt == 3) {
            if (index - Aux > 0) {         //Si data non vide
              int Longitude_size = index - Aux;
              for (int i = 0; i < Longitude_size; i++) {
                donnee_GPS->longitude[i] = trameGGA->trame[Aux];
                Aux++;
              }
              Aux = index + 1;
              index++;
              total_size = total_size + Longitude_size;
              radio_qualite_gps = radio_qualite_gps | 0x02;
            }
            else {
              donnee_GPS->longitude[0] = 'N';
              donnee_GPS->longitude[1] = 'a';
              donnee_GPS->longitude[2] = 'n';
              donnee_GPS->longitude[3] = '\0';
              for (int i = 0; i < TAILLE_LONG; i++) {
                Aux++;
              }
              Aux = index + 1;
              index++;
            }
          }

          // >> Latitude
          if (c_cpt == 5) {
            if (index - Aux > 0) {         //Si data non vide
              int Latitude_size = index - Aux;
              for (int i = 0; i < Latitude_size; i++) {
                donnee_GPS->latitude[i] = trameGGA->trame[Aux];
                Aux++;
              }
              Aux = index + 1;
              index++;
              total_size = total_size + Latitude_size;
              radio_qualite_gps = radio_qualite_gps | 0x01;
            }
            else {
              donnee_GPS->latitude[0] = 'N';
              donnee_GPS->latitude[1] = 'a';
              donnee_GPS->latitude[2] = 'n';
              donnee_GPS->latitude[3] = '\0';
              for (int i = 0; i < TAILLE_LAT; i++) {
                Aux++;
              }
              Aux = index + 1;
              index++;
            }
          }

          // >> AltitudeGPS
          if (c_cpt == 10) {
            if (index - Aux > 0) {         //Si data non vide
              int AltitudeGPS_size = index - Aux;
              for (int i = 0; i < AltitudeGPS_size; i++) {
                donnee_GPS->altitudeGPS[i] = trameGGA->trame[Aux];
                Aux++;
              }
              Aux = index + 1;
              index++;
              total_size = total_size + AltitudeGPS_size;
              fin_data = false;
              radio_qualite_gps = radio_qualite_gps | 0x04;
            }
            else {
              donnee_GPS->altitudeGPS[0] = 'N';
              donnee_GPS->altitudeGPS[1] = 'a';
              donnee_GPS->altitudeGPS[2] = 'n';
              donnee_GPS->altitudeGPS[3] = '\0';
              for (int i = 0; i < TAILLE_ALT; i++) {//sizeof(AltitudeGPS)
                Aux++;
              }
              Aux = index + 1;
              index++;
              fin_data = false;
            }
          }
        }
        else {
          if (trameGGA->trame[index] == 13) {
            fin_data = false;
          }
          else {
            index++;
          }
        }
      }
      donnee_GPS->qualite_signal = radio_qualite_gps;
    





    //<<-------------<< Affichage GPS Data >>------------->>//
    if(PRINT_MSG_SERIAL)
    {
      Serial.print("UTC : ");
      for (int k = 0; k < (sizeof(donnee_GPS->utc)); k++) {
        Serial.print(donnee_GPS->utc[k]);
      }
      Serial.print(" ");
      Serial.print("Longitude : ");
      for (int k = 0; k < (sizeof(donnee_GPS->longitude)); k++) {
        Serial.print(donnee_GPS->longitude[k]);
      }
      Serial.print(" ");
      Serial.print("Latitude : ");
      for (int k = 0; k < (sizeof(donnee_GPS->latitude)); k++) {
        Serial.print(donnee_GPS->latitude[k]);
      }
      Serial.print(" ");
      Serial.print("AltitudeGPS : ");
      for (int k = 0; k < (sizeof(donnee_GPS->altitudeGPS) ); k++) {
        Serial.print(donnee_GPS->altitudeGPS[k]);
      }
      Serial.println("");
    }
    //<<--------------------------------------------------->>//
}

// bool lectureGGA(trameNMEA *GPSBuffer)
// {
//   bool gps_buff_good = false;
//     if (lectureNMEA(GPSBuffer))
//     {
//       gps_buff_good=isGGA(GPSBuffer);
//       if (gps_buff_good)
//       {
//           flush();
//       }
      
//     }
//   return gps_buff_good;
// }

void flush()
{
  while (gps_port.available()) 
  { 
    char inChar = gps_port.read();
  }//vide buffer
  if(PRINT_MSG_SERIAL)
  {
    Serial.println("FLUSH");
  }
}

bool lectureNMEA(trameNMEA *GPSBuffer){
  char inByte;
  bool detect_new_line=false;
  bool gps_buff_good = false;

  if (gps_port.available()) {
    detect_new_line=true;
  }
    
  while (detect_new_line)
  {
      inByte = gps_port.read();
    
      //Serial.print(inByte); // Output exactly what we read from the GPS to debug    
      if ((inByte =='$') || (GPSBuffer->taille >= 150)){
        GPSBuffer->taille = 0;
      }      
      if (inByte != '\r' && inByte != '\n'){
        GPSBuffer->trame[GPSBuffer->taille++] = inByte;
      }   
      if (inByte == '\n'){
        GPSBuffer->trame[GPSBuffer->taille++] = '\0';
        detect_new_line=false;
        gps_buff_good = true;
      }
      if (!gps_port.available())
      {
        detect_new_line=false;
      }
  }

  if(PRINT_MSG_SERIAL && gps_buff_good)
    {
      Serial.print("---->");
      Serial.println(GPSBuffer->trame);
    }
  return gps_buff_good;
}

bool isGGA(trameNMEA *GPSBuffer){
  return (GPSBuffer->trame[1] == 'G' 
            && (GPSBuffer->trame[2] == 'P' || GPSBuffer->trame[2] == 'N') 
            && GPSBuffer->trame[3] == 'G' 
            && GPSBuffer->trame[4] == 'G' 
            && GPSBuffer->trame[5] == 'A');
}

bool isRMC(trameNMEA *GPSBuffer)
{
  return (GPSBuffer->trame[1] == 'G' 
            && (GPSBuffer->trame[2] == 'P' || GPSBuffer->trame[2] == 'N') 
            && GPSBuffer->trame[3] == 'R' 
            && GPSBuffer->trame[4] == 'M' 
            && GPSBuffer->trame[5] == 'C');
}

void read_date_RMC(trameNMEA *trameGGA,char date[TAILLE_DATE])
{
  bool fin_data = true;
  int total_size = 0;
  int c_cpt = 0;
  int index = 0;
  int Aux = 0;

  while (index < (trameGGA->taille) && fin_data) {
    
    if (trameGGA->trame[index] == ',') {
      c_cpt++ ;

      switch (c_cpt)
      {
      case 10:
        fin_data = false;
        if (index - Aux > 0) {         //Si data non vide
          int date_size = index - Aux;
          for (int i = 0; i < date_size; i++) {
            date[i] = trameGGA->trame[Aux];
            Aux++;
          }
          date[6]= '\0';
          Aux = index + 1;
          index++;
        }
        else {
          date[0] = 'N';
          date[1] = 'a';
          date[2] = 'n';
          date[3] = '\0';
          for (int i = 0; i < sizeof(date); i++) {
            Aux++;
          }
          Aux = index + 1;
          index++;
        }
        break;
      
      default:
        Aux = index + 1;
        break;
      }
    }
    index++;
  }
  
}