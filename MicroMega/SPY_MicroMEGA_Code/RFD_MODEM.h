#if !defined(RFD_MODEM_H)
#define RFD_MODEM_H


#include "Termometre_DS18B20.h"
#include "Hygrometre_BMP388.h"
#include "Barometre_HTU21D-F.h"

#include "GPS_NEO-6M.h"
#include "Alphasense_A4.h"



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

void setupRadio();
void sendATCommand(String command);
void _attente();

void ecriture_radio(
                    char temp[TAILLE_TEMP],
                    char hum[TAILLE_HUM],
                    char pres[TAILLE_PRES],
                    donnee_GPS *donnee_GPS,
                    char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO]
                    );

#endif // RFD_MODEM_H
