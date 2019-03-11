/**
 * phoenix_encoders.h
 **/

#pragma once
#include <stdint.h>

// Number of encoders
#define NUM_ENCODERS 3

/**
 * Azzera tutto l'array di _encoder_current_value ed
 * _encoder_sampled_value.
 * Azzera _encoder_prev ed
 * inizializza gli encoder impostando il registro K 
 * come Input-Pullup (DDRK a 0 e PORTK a 1 per il bit i-esimo)
 * Poi abilita l'Interrupt Change 2 attivando il secondo bit di PCICR
 * Infine imposta i bit di PCMSK2 pari a ENCODER_MASK
 **/
void Encoder_init(void);

/**
 * Copia i valori presenti in _encoder_current_value
 * in _encoder_sampled_value.
 * La funzione deve avvenire senza interruzioni.
 **/
void Encoder_sample(void);

/**
 * Restituisce il num_encoder-esimo valore
 * di _encoder_sampled_value
 **/
uint16_t Encoder_getValue(uint8_t num_encoder);
