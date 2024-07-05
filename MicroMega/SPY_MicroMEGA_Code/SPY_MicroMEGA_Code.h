#if !defined(SPY_MICRO_MEGA_CODE)
#define SPY_MICRO_MEGA_CODE

#include <stdint.h>

const bool PRINT_MSG_SERIAL = false;

/**
 * @brief Structure représentant les temps d'exécution des différentes fonctions.
 * 
 * Cette structure contient les temps d'exécution (en millisecondes) des différentes fonctions du programme.
 */
struct temps_fonction
{
  uint16_t setupRadio;
  uint16_t temperature;
  uint16_t humidity;
  uint16_t barometre;
  int16_t gps_read;
  uint16_t split;
  uint16_t alphasens;
};

#endif // SPY_MICRO_MEGA_CODE
