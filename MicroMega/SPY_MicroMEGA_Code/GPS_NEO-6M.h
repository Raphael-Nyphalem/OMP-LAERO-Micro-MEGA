#if !defined(GPS_NEO_6M)
#define GPS_NEO_6M

#include <stdint.h>

#include "SPY_MicroMEGA_Code.h"
#include <ArduinoSTL.h>
/*
attention line 22 de ArduinoSTL commenter (si erreur " multiple definition of `std::nothrow' " )
C:\Users\micromega_adm\Documents\Arduino\libraries\ArduinoSTL\src\new_handler.cpp
// const std::nothrow_t std::nothrow = { };

source réponce: https://github.com/mike-matera/ArduinoSTL/issues/84
*/

//TX_GPS bleu -> RX_Mega 19
//RX_GPS blanc -> TX_Mega 18
#define gps_port Serial1
#define newGPSBaud 115200


const uint8_t TAILLE_UTC = 9;
const uint8_t TAILLE_LONG = 11;
const uint8_t TAILLE_LAT = 11;
const uint8_t TAILLE_ALT = 5;
const uint8_t TAILLE_DATE = 7;

const unsigned char UBLOX_INIT[] = {
  0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0x96, //baudrate 115200 pt1
};
const uint8_t MAX_GGA = 150;
const uint16_t MAX_SERIAL_GPS = 400;

/**
 * @struct trameNMEA
 * @brief Structure pour stocker une trame NMEA.
 */
struct trameNMEA
{
  char trame[MAX_GGA];
  uint8_t taille = 0;
};

/**
 * @struct donnee_GPS
 * @brief Structure pour stocker les données GPS.
 */
struct donnee_GPS
{
  char utc[TAILLE_UTC] = {0};                    //GPS data
  char longitude[TAILLE_LONG] = {0};
  char latitude[TAILLE_LAT] = {0};
  char altitudeGPS[TAILLE_ALT] = {0};
  char qualite_signal = 0x00;
  uint8_t nombre_satelite = 0;
};


/**
 * @brief Initialise le module GPS NEO-6M.
 * 
 * Cette fonction configure le port série pour communiquer avec le module GPS NEO-6M,
 * envoie les données de configuration au module et change la vitesse de communication.
 */
void initGPS();

/**
 * @brief Lit et copie une trame NMEA GGA à partir du buffer GPS.
 * 
 * Cette fonction copie la trame NMEA GGA du buffer GPS dans une autre structure de trame.
 * 
 * @param[in] GPSBuffer Pointeur vers la structure contenant les données GPS en buffer.
 * @param[out] trameGGA Pointeur vers la structure où la trame GGA sera copiée.
 */
void lecture_gps(trameNMEA *GPSBuffer,trameNMEA *trameGGA);

/**
 * @brief Extrait les données de la trame NMEA GGA et les stocke dans une structure de données GPS.
 * 
 * Cette fonction analyse une trame NMEA GGA et extrait les informations telles que l'UTC, la longitude,
 * la latitude et l'altitude, et les stocke dans la structure de données "donnee_GPS".
 * 
 * Chaque bit de radio_qualite_gps représente la disponibilité d'une donnée particulière :
 * Bit 0 (0x01) : Disponibilité de la latitude.
 * Bit 1 (0x02) : Disponibilité de la longitude.
 * Bit 2 (0x04) : Disponibilité de l'altitude GPS.
 * Bit 3 (0x08) : Disponibilité de l'heure UTC.       
 * 
 * @param[in] trameGGA Pointeur vers la structure contenant la trame NMEA GGA.
 * @param[out] donnee_GPS Pointeur vers la structure où les données GPS seront stockées.
 */
void split_trame_gga(trameNMEA *trameGGA,struct donnee_GPS *donnee_GPS);


// bool lectureGGA(trameNMEA *GPSBuffer);

/**
 * @brief Vide le tampon de réception du port GPS.
 * 
 * Cette fonction lit et jette tous les caractères disponibles dans le tampon de réception du port GPS.
 * Si l'option PRINT_MSG_SERIAL est activée, elle affiche "FLUSH" via la liaison série.
 */
void flush();

/**
 * @brief Analyse les données NMEA reçues du module GPS.
 * 
 * Cette fonction lit les données NMEA du module GPS et les stocke dans un buffer.
 * 
 * @param[out] GPSBuffer Pointeur vers la structure où les données NMEA seront stockées.
 */
bool lectureNMEA(trameNMEA *GPSBuffer);

/**
 * @brief Vérifie si la trame NMEA est une trame GGA.
 * 
 * Cette fonction vérifie si la trame NMEA en buffer est de type GGA.
 * 
 * @param[in] GPSBuffer Pointeur vers la structure contenant les données NMEA.
 * @return true si la trame est de type GGA 
 * @return false sinon
 */
bool isGGA(trameNMEA *GPSBuffer);

/**
 * @brief Vérifie si la trame NMEA est de type RMC.
 * 
 * @param GPSBuffer Pointeur vers une structure trameNMEA contenant la trame NMEA à vérifier.
 * @return true si la trame correspond au type RMC, false sinon.
 */
bool isRMC(trameNMEA *GPSBuffer);

/**
 * @brief Lit la date à partir d'une trame NMEA de type RMC.
 * 
 * Cette fonction parcourt la trame NMEA pour extraire la date à partir du 10ème champ séparé par des virgules (,).
 * Si le champ n'est pas présent ou est vide, elle retourne une chaîne "NaN".
 * 
 * @param trameGGA Pointeur vers une structure trameNMEA contenant la trame NMEA à analyser.
 * @param date Tableau de caractères où la date extraite sera stockée (doit être de taille suffisante, au moins 7 caractères).
 */
void read_date_RMC(trameNMEA *trameGGA,char date[TAILLE_DATE]);

#endif // GPS_NEO_6M
