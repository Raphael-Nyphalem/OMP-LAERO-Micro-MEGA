#if !defined(TERMOMETRE_DS18B20)
#define TERMOMETRE_DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10

const uint8_t TAILLE_TEMP = 7;

/**
 * @brief Initialise le capteur de température DS18B20.
 * 
 * Cette fonction initialise la communication avec le capteur DS18B20.
 */
void init_termometre();

/**
 * @brief Lit la température à partir du capteur DS18B20.
 * 
 * Cette fonction effectue une lecture de la température à partir du capteur DS18B20 et stocke la valeur
 * mesurée dans une chaîne de caractères. Si la lecture échoue (valeur -127.0°C), la valeur "Nan" est renvoyée.
 * 
 * @param[out] temp Tableau de caractères où la température sera stockée.
 * 
 * @note La température est exprimée en degrés Celsius (°C).
 */
void lecture_temp(char temp[TAILLE_TEMP]);

#endif // TERMOMETRE_DS18B20
