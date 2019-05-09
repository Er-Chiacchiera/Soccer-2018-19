
/**
 * ares_ultrasouno.cpp
 */

#include "ares_ultrasuono.h"


/*
 * Questa funzione si occupa di azzerare le variabili:
 * distanza e durata
 */
void PhoenixUltrasound_init(Ultrasound * u){
    pinMode(u->trigger_port, OUTPUT);
    pinMode(u->echo_port, INPUT);

    u->distanza = 0;
    u->durata = 0;
}

/**
 * 
 * Questa funzione si occupa di interrogare il singolo sensore
 * e di tirare fuori un valore che verrà inserito nella variabile
 * "distanza" con la seguente formula:
 * 
 * distanza = 0.034 * durata / 2
 * 
 * calcola anche il valore di durara dell'impulso: 
 * 
 * durata = pulseIn(echo_port)
 * 
 * Se il valore di distanza < soglia_ultrasound -> detect_wall = 1
 * Se il valore di distanza > soglia_ultrasound -> detect_wall = 0   
 */
void PhoenixUltrasound_handle(Ultrasound * u){
        digitalWrite(u->trigger_port, LOW);
        digitalWrite(u->trigger_port, HIGH);
        delayMicroseconds( 10 );
        digitalWrite(u->trigger_port, LOW);
        u->durata = pulseIn(u->echo_port, HIGH);
        u->distanza = 0.034 * u->durata / 2;
}

/**
 * Questa funzione si occupa di azzerare le variabili:
 * distanza e durata 
 */

void PhoenixUltrasound_reset(Ultrasound * u){
    u->distanza = 0;
    u->durata = 0;
}

/**
 * Questa funzione ritorna il valore di detect_wall
 */
int PhoenixUltrasound_getWallStatus(Ultrasound * u){
        return u->detect_wall;
}

/**
 * Questa funzione ritorna il valore di distanza
 */
int PhoenixUltrasound_returnDistance(Ultrasound * u){
        return u->detect_wall;
}