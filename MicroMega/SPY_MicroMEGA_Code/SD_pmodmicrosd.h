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
 * @brief Écriture des données dans un fichier sur une carte SD.
 * 
 * Cette fonction écrit les données passées en paramètres dans un fichier spécifié sur une carte SD.
 * Elle utilise un format de trame défini pour organiser les différentes informations.
 * 
 * @param sd_filename Nom du fichier sur la carte SD où écrire les données.
 * @param id Identifiant à enregistrer dans le fichier.
 * @param pgmTime Temps du programme au moment de l'enregistrement.
 * @param temp Tableau de caractères représentant la température.
 * @param hum Tableau de caractères représentant l'humidité.
 * @param pres Tableau de caractères représentant la pression.
 * @param temp_baro Tableau de caractères représentant la température barométrique.
 * @param donnee_GPS Pointeur vers une structure contenant les données GPS.
 * @param adc1 Pointeur vers une structure contenant les données du premier capteur Alphasense.
 * @param adc2 Pointeur vers une structure contenant les données du second capteur Alphasense.
 * 
 * @note Cette fonction vérifie si le fichier spécifié existe et est ouvert avec succès avant d'écrire les données.
 * Elle gère également les cas où la carte SD n'est pas détectée ou où il y a des erreurs de connexion.
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
                donnee_Alphasense* adc2,
                char date[TAILLE_DATE]
                );


#endif // SD_PMODMICROSD
