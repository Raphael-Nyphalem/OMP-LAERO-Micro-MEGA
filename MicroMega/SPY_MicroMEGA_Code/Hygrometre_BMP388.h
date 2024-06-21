#if !defined(HYGROMETRE_BMP388)
#define HYGROMETRE_BMP388

#include <Wire.h>
#include "cactus_io_HTU21D.h"

const uint8_t TAILLE_HUM = 7;


/**
 * @brief Initialise le capteur d'humidité HTU21D.
 * 
 * Cette fonction configure le capteur HTU21D pour la lecture de l'humidité et de la température.
 * 
 * @note Seules les mesures d'humidité seront exploitées.
 * @note En cas d'échec de la connexion avec le capteur, un message d'erreur est affiché sur le port série.
 */
void init_hygrometre();

/**
 * @brief Lit l'humidité à partir du capteur HTU21D.
 * 
 * Cette fonction effectue une lecture de l'humidité à partir du capteur HTU21D et stocke la valeur
 * mesurée dans une chaîne de caractères. Si la lecture échoue ou si l'humidité est hors des limites,
 * la valeur "Nan" est renvoyée.
 * 
 * @param[out] hum Tableau de caractères où l'humidité sera stockée.
 * 
 * @note L'humidité est exprimée en pourcentage (%).
 * @note En cas d'échec de la lecture, un message d'erreur est affiché sur le port série.
 */
void lecture_humidite(char hum[TAILLE_HUM]);

#endif // HYGROMETRE_BMP388

