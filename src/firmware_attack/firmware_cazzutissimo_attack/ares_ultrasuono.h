
/**
 *   ares_ultrasuono.h 
 */

#pragma once
#include <Arduino.h>
#include "ares_params.h"



typedef struct{
    const int trigger_port;
    const int echo_port;
    long distanza;
    long durata;
    int soglia_ultrasound;
    int detect_wall;
} Ultrasound;

/**
 * Questa funzione si occupa di azzerare le variabili:
 * distanza e durata
 */
void PhoenixUltrasound_init(Ultrasound * u);
/**
 * 
 * Questa funzione si occupa di interrogare il singolo sensore
 * e di tirare fuori un valore che verrà inserito nella variabile
 * "distanza" con la seguente formula:
 * 
 * distanza = 0.034 * durata / 2
 * 
 * Se il valore di distanza < soglia_ultrasound -> detect_wall = 1
 * Se il valore di distanza < soglia_ultrasound -> detect_wall = 0
 */
void PhoenixUltrasound_handle(Ultrasound * u);
/**
 * Questa funzione si occupa di azzerare le variabili:
 * distanza e durata 
 */
void PhoenixUltrasound_reset(Ultrasound * u);

/**
 * Questa funzione ritorna il valore di detect_wall
 */
int PhoenixUltrasound_getWallStatus(Ultrasound * u);

/**
 * Questa funzione ritorna il valore di distanza
 */
int PhoenixUltrasound_returnDistance(Ultrasound * u);