#if !defined(RFD_MODEM_H)
#define RFD_MODEM_H

#include <SoftwareSerial.h>
#include <Arduino.h>

const bool DEBUG = true;

const String NETID = "169"; // network de 0 a 255 defaut 30
const String TXPOWER = "10"; // de 0 a 30 defaut 30


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

void setupRadio(void);
void sendATCommand(String command);
void attente();
bool lecture(char tab[MAX_TRAME_RECEPTION]);
void del_tableau(char tab[MAX_TRAME_RECEPTION]);
bool detection(char charLu,char signe,bool *flag_1_lu);

#endif // RFD_MODEM_H
