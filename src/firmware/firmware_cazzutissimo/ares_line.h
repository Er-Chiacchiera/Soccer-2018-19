/**
 * phoenix_line.h
 **/

#pragma once
#include <Arduino.h>
#include "ares_params.h"
#include "ares_line_internal.h"

#define ESCAPE_TTL 10

// Funzioni utili per lavorare con la maschera.
uint8_t mask_read(uint16_t* mask, uint8_t index);
void mask_setBit(uint16_t* mask, uint8_t index);
void mask_clearBit(uint16_t* mask, uint8_t index);

typedef struct {
  PhoenixLineSensor* line_sensors;
  uint8_t escape_flag;
  double escape_x;
  double escape_y;

  /**
   * La maschera viene usata per evitare di leggere piu' di una volta
   * lo stesso sensore.
   * Guardiamo la variabile mask a livello di memoria:
   * In binario mask è rappresentata cosi:
   * mask : 0000 0000 0000 0000 (16 bit posti a 0)
   *
   * quando un sensore rileva la linea, il bit associato al suo indice
   * nell'array line_sensors, viene impostato ad 1 (ad esempio viene
   * rilevato il sensore in posizione 2, mask viene aggioranto cosi:
   * 0000 0000 0000 0100 [ricorda che la posizione 0 conta !])
   *
   * Quando eseguo la lettura, prima di leggere un sensore, guardo se
   * il bit associato alla sua posizione e' pari a 1. Se lo e' allora
   * passo al sensore successivo.
   *
   * Ultimo esempio: Supponi che il sensore 0, 2, 3 abbiano rilevato
   * la linea, allora la variabile mask avrà questa forma:
   * 0000 0000 0000 1101
   * 
   * Per scrivere ad una certa posizione della maschera puoi usare le seguenti
   * funzioni:
   * Lettura di un bit j della maschera: mask_read(&d->mask, j)
   * Scrittura di un bit j della maschera: mask_set(&d->mask, j)
   * Azzeramento di un bit j della maschera: mask_clear(&d->mask, j)
  **/
  uint16_t mask=0;

  uint8_t calib_flag;
  uint16_t escape_ttl;
} PhoenixLineHandler;

/**
 * inizializza d (PhoenixLineHandler) azzerando i valori di
 * escape_flag, escape_x ed escape_y ed impostando 
 * la variabile escape_ttl pari a ESCAPE_TTL
 * Poi assegna la variabile line_sensors = s 
 **/
void PhoenixLineHandler_init(PhoenixLineHandler* d, PhoenixLineSensor* s);

/**
 * Parte difficile :)
 *
 * lancia la funzione PhoenixLineSensor_handle su tutti i sensori
 * presenti nell'array d->line_sensors
 *
 * In caso calib_flag fosse 1, la funzione puo' fermarsi qui...
 * 
 * In modo ciclico, per ogni sensore nell'array d->line_sensors
 * controlla se il bit associato al sensore nella maschera (d->mask)
 * e' pari ad 1. In tal caso la lettura procede al sensore successivo.
 * Se il bit e' 0 invece, bisogna controllare lo stato del sensore
 * ( usa la funzione PhoenixLineSensor_getStatus ).
 * Se lo stato e' positivo allora bisogna:
 *  -impostare ad 1 il bit della maschera associata al sensore
 *  -sommare ad escape_x il valore x del sensore analizzato
 *  -sommare ad escape_y il valore y del sensore analizzato
 *  -impostare ad 1 la variabile escape_flag
 *  -impostare ad ESCAPE_TTL la variabile escape_ttl
 *
 * Al termine dei controlli sui sensori, se escape_flag e' attiva,
 * devi decrementare di 1 il valore di escape_ttl.
 * Se il valore di escape_ttl e' pari a 0, allora deve essere eseguita
 * la funzione PhoenixLineHandler_reset
 */
void PhoenixLineHandler_handle(PhoenixLineHandler* d);

/**
 * restituisce il valore di escape_flag
 **/
uint8_t PhoenixLineHandler_getStatus(PhoenixLineHandler* d);

/**
 * restituisce il valore di escape_x
 **/
double PhoenixLineHandler_getEscapeX(PhoenixLineHandler* d);

/**
 * restituisce il valore di escape_x
 **/
double PhoenixLineHandler_getEscapeY(PhoenixLineHandler* d);

/**
 * deve azzerare la variabile escape_flag, escape_x, escape_y e 
 * mask.
 * Per ogni sensore poi, bisogna lanciare la funzione 
 * PhoenixLineSensor_reset
 **/
void PhoenixLineHandler_reset(PhoenixLineHandler* d);

/**
 * imposta calib_flag pari ad 1, e lancia la funzione 
 * PhoenixLineSensor_startCalib per ogni sensore in line_sensors 
 **/
void PhoenixLineHandler_startCalib(PhoenixLineHandler* d);

/**
 * azzera calib_flag e lancia la funzione PhoenixLineSensor_stopCalib
 * per ogni sensore in line_sensors
 **/
void PhoenixLineHandler_stopCalib(PhoenixLineHandler* d);
