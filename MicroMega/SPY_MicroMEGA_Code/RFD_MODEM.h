#if !defined(RFD_MODEM_H)
#define RFD_MODEM_H


#include "Termometre_DS18B20.h"
#include "Hygrometre_BMP388.h"
#include "Barometre_HTU21D-F.h"

#include "GPS_NEO-6M.h"
#include "Alphasense_A4.h"


const String NETID = "170"; // network de 0 à 499 defaut 30
const String TXPOWER = "10"; // de 0 à 30 defaut 30
const String DUTY_CYCLE = "1";// de 1 à 100 duty cycle
const String AIR_SPEED = "188";// 2 à 250 -> 188 vitesse dans l'air 188 000 bit/s

// Constantes pour les commandes AT et autres configurations
const char START_COMMANDE_AT[3] = "+++";
const String SHOW_RADIO_VERSION = "ATI";
const String SHOW_BOARD_TYPE = "ATI2";
const String SHOW_BOARD_FREQUENCY = "ATI3";
const String SHOW_BOARD_VERSION = "ATI4";
const String SHOW_EEPROM_PARAM_VALUES = "ATI5";
const String SHOW_EEPROM_PARAM_RANGE_OF_VALUES = "ATI5?";
const String STOP_COMMANDE_AT = "ATO";
const String REBOOT = "ATZ";
const uint8_t MAXTRAME = 64;
const uint8_t TAILLE_INDICE = 1;
const uint8_t TAILLE_SIGNE = 1;
const char SIGNE_DEBUT_TRAME = '#';
const char SIGNE_FIN_TRAME = '$';

/**
 * @brief Initialise le module radio avec les paramètres nécessaires.
 * 
 * Cette fonction configure le port série utilisé pour communiquer avec le module radio.
 * Elle envoie des commandes AT pour configurer certains paramètres du module.
 * 
 * @note Cette fonction utilise des commandes spécifiques et des délais pour l'initialisation.
 */
void setupRadio();

/**
 * @brief Envoie une commande AT au module radio et affiche la réponse.
 * 
 * @param command Commande AT à envoyer sous forme de chaîne String.
 * 
 * @note Cette fonction envoie la commande via le port série et attend une réponse.
 * Elle affiche la commande envoyée ainsi que la réponse reçue sur la liaison série.
 */
void sendATCommand(String command);

/**
 * @brief Fonction d'attente de réponse du module radio.
 * 
 * Cette fonction attend la réponse du module radio après l'envoi d'une commande.
 * Elle affiche la réponse reçue sur la liaison série.
 * 
 * @note Cette fonction est utilisée pour attendre la réponse du module radio après certaines commandes AT.
 */
void _attente();

/**
 * @brief Fonction pour écrire et envoyer des données via le module radio NRF24L01+.
 * 
 * @param temp Tableau de caractères représentant la température.
 * @param hum Tableau de caractères représentant l'humidité.
 * @param pres Tableau de caractères représentant la pression.
 * @param donnee_GPS Pointeur vers une structure contenant des données GPS.
 * @param tab_adc_brut_radio Tableau de caractères représentant les données ADC pour le module radio.
 * 
 * @note Cette fonction construit une trame de données et l'envoie via le module radio.
 * Elle gère également l'affichage de débogage si l'option PRINT_MSG_SERIAL est activée.
 */
void ecriture_radio(
                    char temp[TAILLE_TEMP],
                    char hum[TAILLE_HUM],
                    char pres[TAILLE_PRES],
                    donnee_GPS *donnee_GPS,
                    char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO]
                    );

#endif // RFD_MODEM_H
