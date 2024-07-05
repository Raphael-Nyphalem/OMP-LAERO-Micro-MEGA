#if !defined(RFD_MODEM_H)
#define RFD_MODEM_H

#include <SoftwareSerial.h>
#include <Arduino.h>

const bool DEBUG = true;

const String NETID = "170"; // network de 0 à 255 defaut 30
const String TXPOWER = "10"; // de 0 à 30 defaut 30
const String DUTY_CYCLE = "1";//de 1 à 100 duty cycle
const String AIR_SPEED = "188";//188 vitesse dans l'air 188 000 bit/s

const char START_COMMANDE_AT[3] = "+++";
const String SHOW_RADIO_VERSION = "ATI";
const String SHOW_BOARD_TYPE = "ATI2";
const String SHOW_BOARD_FREQUENCY = "ATI3";
const String SHOW_BOARD_VERSION = "ATI4";
const String SHOW_EEPROM_PARAM_VALUES = "ATI5";
const String SHOW_EEPROM_PARAM_RANGE_OF_VALUES = "ATI5?";

const String STOP_COMMANDE_AT = "ATO";
const String REBOOT = "ATZ";


const uint8_t pinRX = 11;
const uint8_t pinTX = 10;


const uint8_t MAX_TRAME_RECEPTION = 60;
const uint8_t TAILLE_INDICE = 1;

/**
 * @brief Configuration initiale du module radio.
 * 
 * Cette fonction initialise la communication avec le module radio en configurant
 * différents paramètres comme la vitesse de transmission, le NETID, la puissance
 * d'émission, le cycle de devoir, etc.
 */
void setupRadio(void);

/**
 * @brief Envoie une commande AT au module radio et attend une réponse.
 * 
 * Cette fonction envoie la commande AT spécifiée au module radio via la liaison série.
 * Elle attend ensuite la réponse du module et affiche cette réponse sur le port série.
 * Si aucune réponse n'est reçue dans les 700 millisecondes, elle affiche un message
 * indiquant l'absence de réponse.
 * 
 * @param command La commande AT à envoyer au module radio.
 */
void sendATCommand(String command);

/**
 * @brief Attend une réponse du module radio.
 * 
 * Cette fonction attend une réponse du module radio sur la liaison série.
 * Si aucune réponse n'est reçue dans les 500 millisecondes, elle affiche un message
 * indiquant l'absence de réponse.
 */
void attente();

/**
 * @brief Lit une trame reçue par le module radio.
 * 
 * Cette fonction lit une trame reçue par le module radio via la liaison série.
 * Elle détecte le début et la fin de la trame en cherchant les caractères '#'
 * et '$' respectivement. Une fois la trame complète détectée, elle la retourne.
 * 
 * @param tab Tableau de caractères où stocker la trame reçue.
 *        La taille du tableau est définie par MAX_TRAME_RECEPTION.
 * @return true si une trame complète a été lue, sinon false.
 */
bool lecture(char tab[MAX_TRAME_RECEPTION]);

/**
 * @brief Initialise un tableau de caractères avec des '0'.
 * 
 * Cette fonction initialise tous les éléments d'un tableau de caractères
 * avec le caractère '0'.
 * 
 * @param tab Tableau de caractères à initialiser.
 *        La taille du tableau est définie par MAX_TRAME_RECEPTION.
 */
void del_tableau(char tab[MAX_TRAME_RECEPTION]);

/**
 * @brief Détecte la présence d'un caractère spécifique et gère un drapeau.
 * 
 * Cette fonction vérifie si un caractère spécifique est détecté et gère un drapeau
 * pour indiquer si le caractère a été lu une fois ou non.
 * 
 * @param charLu Caractère à vérifier.
 * @param signe Caractère à détecter.
 * @param flag_1_lu Pointeur vers un booléen indiquant si le caractère a été lu.
 * @return true si le caractère détecté correspond à 'signe' et n'a été lu qu'une fois,
 *         sinon false.
 */
bool detection(char charLu,char signe,bool *flag_1_lu);

#endif // RFD_MODEM_H
