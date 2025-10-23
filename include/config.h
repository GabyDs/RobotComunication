#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Incluir el archivo con las MACs privadas
#include "secrets.h"

// Constante para el número de receptores
extern const uint8_t RECEIVERS_COUNT;

// Array de punteros a las direcciones MAC
extern const uint8_t* RECEIVERS_MACS[];

#endif
