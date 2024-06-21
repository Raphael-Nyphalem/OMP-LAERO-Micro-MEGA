#if !defined(BAROMETRE_HTU21D_F)
#define BAROMETRE_HTU21D_F

#include <SPI.h>
#include "Adafruit_BMP3XX.h"


#define BMP_SCK 46  //52
#define BMP_MISO 44 //50
#define BMP_MOSI 45 //51
#define BMP_CS 47   //53
#define SEALEVELPRESSURE_HPA (1013.25) //la pression au niveau de la mer 1013.25

const uint8_t TAILLE_PRES = 7;
const uint8_t TAILLE_TEMP_BARO = 7;

/**
 * @brief Initialise le capteur barométrique BMP3XX en mode SPI.
 * 
 * Cette fonction configure le capteur BMP3XX en mode SPI et initialise les paramètres
 * d'oversampling pour la température et la pression, le coefficient du filtre IIR,
 * ainsi que le taux de données en sortie.
 * 
 * @note Seules les mesures de pression seront exploitées.
 * @note En cas d'échec de la connexion avec le capteur, un message d'erreur est affiché sur le port série.
 */
void init_barometre();

/**
 * @brief Lit la pression barométrique à partir du capteur BMP3XX.
 * 
 * Cette fonction effectue une lecture du capteur BMP3XX et stocke la pression mesurée
 * dans une chaîne de caractères. Si la lecture échoue ou si la pression est hors des
 * limites (300-1100 hPa), la valeur "Nan" est renvoyée.
 * 
 * @param[out] pres Tableau de caractères où la pression sera stockée.
 * 
 * @note La pression est exprimée en hectopascals (hPa).
 * @note En cas d'échec de la lecture, un message d'erreur est affiché sur le port série.
 */
void lecture_barometre(char pres[TAILLE_PRES],char temp_baro[TAILLE_TEMP_BARO]);

#endif // BAROMETRE_HTU21D_F
