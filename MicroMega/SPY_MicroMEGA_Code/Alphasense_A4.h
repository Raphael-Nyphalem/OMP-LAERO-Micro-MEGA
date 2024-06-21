#if !defined(ALPHASENSE_GAZ)
#define ALPHASENSE_GAZ

#include <SPI.h>
#include "SPY_MicroMEGA_Code.h"

//===== Alphasense ====//
#define ADC1_EOC 2
#define ADC1_CS 3
#define ADC2_EOC 4
#define ADC2_CS 5

const uint8_t TAILLE_TAB_DATA_ADC_RADIO = 32;

/**
 * @brief Structure de données pour stocker les résultats des capteurs Alphasense.
 * 
 * Cette structure est utilisée pour stocker les résultats des mesures des capteurs Alphasense.
 * Chaque champ représente la valeur numérique mesurée pour un canal spécifique du capteur.
 * Les données sont stockées sous forme d'entiers non signés sur 16 bits.
 */
struct donnee_Alphasense
{
  uint16_t data_out_ch0 = 0;
  uint16_t data_out_ch1 = 0;
  uint16_t data_out_ch2 = 0;
  uint16_t data_out_ch3 = 0;
  uint16_t data_out_ch4 = 0;
  uint16_t data_out_ch5 = 0;
  uint16_t data_out_ch6 = 0;
  uint16_t data_out_ch7 = 0;
  uint16_t data_out_ch8 = 0;
  uint16_t data_out_ch10 = 0;
};

/**
 * @brief Initialise les capteurs Alphasense et configure les broches et la communication SPI.
 * 
 * Cette fonction configure les broches pour les Chip Select (CS) et les End of Conversion (EOC) des deux capteurs Alphasense.
 * Elle démarre également la communication SPI et envoie une requête initiale aux deux capteurs pour initialiser la communication.
 * 
 * @note Cette fonction doit être appelée une fois au démarrage du système pour configurer les capteurs.
 */
void init_alphasense();

/**
 * @brief Initialise l'ADC en envoyant des données et en recevant les résultats.
 * 
 * @param data_IN_8b Les données à envoyer à l'ADC (8 bits).
 * @param ADC_CS Le pin du Chip Select pour l'ADC.
 * 
 * Cette fonction initialise l'ADC en envoyant des données spécifiées et en recevant les résultats convertis.
 * Elle utilise la communication SPI pour cela.
 * 
 * @note La communication SPI doit déjà être configurée avant d'appeler cette fonction.
 * 
 * @param data_IN_8b représente les 8 bits de données à envoyer à l'ADC.
 * 
 * @param ADC_CS est le pin utilisé comme Chip Select pour communiquer avec l'ADC.
 * 
 */
void init_ADC(byte data_IN_8b, int ADC_CS);

/**
 * @brief Effectue l'acquisition de données à partir de deux capteurs Alphasense.
 * 
 * @param adc1 Pointeur vers une structure de données pour stocker les résultats du premier ADC.
 * @param adc2 Pointeur vers une structure de données pour stocker les résultats du deuxième ADC.
 * @param tab_adc_brut_radio Tableau pour stocker les données brutes à des fins de radio.
 * 
 * Cette fonction réalise l'acquisition de données à partir de deux capteurs Alphasense, en envoyant des requêtes
 * et en recevant les résultats via le protocole SPI. Les résultats sont stockés
 * dans les structures de données (donnee_Alphasense) pointées par @p adc1 et @p adc2, et les données brutes sont enregistrées dans
 * le tableau @p tab_adc_brut_radio.
 * 
 * La fonction utilise des délais de 20 microsecondes entre les transactions SPI pour permettre la stabilisation
 * des données.
 * 
 * Si la macro PRINT_MSG_SERIAL est définie, les résultats des deux ADC sont affichés via la liaison série.
 */
void alphasens(struct donnee_Alphasense *adc1,struct donnee_Alphasense *adc2,char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO] );


#endif // ALPHASENSE_GAZ
