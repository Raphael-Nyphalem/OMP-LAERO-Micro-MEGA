#if !defined(SD_PMODMICROSD)
#define SD_PMODMICROSD

#include "SPY_MicroMEGA_Code.h"

#include "Termometre_DS18B20.h"
#include "Hygrometre_BMP388.h"
#include "Barometre_HTU21D-F.h"

#include "GPS_NEO-6M.h"
#include "Alphasense_A4.h"

#include <SD.h>
#include <SPI.h>

#define SD_CS 6

extern String sd_filename;

/**
 * @brief Initialise la carte SD et crée un fichier pour stocker les données.
 * 
 * Configure les broches de la carte SD et initialise la communication avec la carte.
 * Crée un fichier pour stocker les données, en ajoutant un numéro de séquence au nom du fichier s'il existe déjà.
 * @note le dernier fichier crée est celui avec le nombre le plus grand
 */
void init_SD();


/**
 * @brief Écrit les données dans un fichier sur la carte SD.
 * 
 * Écrit les données fournies dans un fichier sur la carte SD.
 * Les données comprennent l'identifiant, les informations GPS, les données des capteurs ADC,
 * la température, l'humidité, la pression, les temps du programme et les trames GPS.
 * 
 * @param sd_filename Nom du fichier sur la carte SD.
 * @param id Identifiant.
 * @param pgmTime Pointeur vers le temps du programme.
 * @param temp Tableau contenant la température.
 * @param hum Tableau contenant l'humidité.
 * @param pres Tableau contenant la pression.
 * @param trameGGA Pointeur vers la structure contenant la trame GPS.
 * @param donnee_GPS Pointeur vers la structure contenant les données GPS.
 * @param adc1 Pointeur vers la structure contenant les données des capteurs ADC1.
 * @param adc2 Pointeur vers la structure contenant les données des capteurs ADC2.
 * @param timeF Pointeur vers la structure contenant les temps.
 */
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
                donnee_Alphasense* adc2);


#endif // SD_PMODMICROSD
