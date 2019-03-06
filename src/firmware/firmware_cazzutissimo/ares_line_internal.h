/**
 * phoenix_line_internal.h
 **/

#pragma once
#include <Arduino.h>

typedef struct {

  // Sezione comune
  double x; // componente x del vettore associato al sensore
  double y; // componente y del vettore associato al sensore
  uint16_t soglia;// soglia riconoscimento linea
  uint16_t misura;// misura attuale del sensore
  uint16_t misura_min;// x Calibrazione: Lettura di valore minimo
  uint16_t misura_max;// x Calibrazione: Lettura di valore massimo
  uint8_t detect_flag;// flag di rilevazione linea ( 1 : linea rilevata )
  uint8_t calibra_flag;// x Calibrazione: flag di calibrazione

  // Sezione gruppo Francesco
  /**
   * Mappatura dei sensori:
   * Ogni modulo ADS1015 ( ADC con interfaccia i2c )
   * puo' controllare fino a 4 sensori.
   * È possibile leggere uno dei 4 sensori collegati al modulo
   * richiedendo al modulo la lettura in posizione i-esima 
   * ( i deve valere minimo 0 e massimo 3)
   *
   * Sul robot sono stati predisposti spazi per 
   * al piu' 4 moduli ADC.
   *
   * Per accedere ad un sensore, bisogna conoscere a quale
   * ADC appartiene (adc_addr) e quale indice bisogna fornire
   * al modulo per ricavare tale lettura (adc_idx)
   *
   **/
  uint8_t adc_addr;// Indice x adc nell'array di ADC
  uint8_t adc_idx;// Indice interno all'adc per l'individuazione
                  // del sensore

  // Sezione gruppo Sara
  /**
   * Ogni sensore e' collegato direttamente ad un analogico
   * di Arduino.
   * Possiamo leggere il valore del sensore, attraverso il pin
   * a cui il sensore e' collegato (pin_reading)
   **/
  uint8_t pin_reading;// Pin relativo al sensore
} PhoenixLineSensor;


/**
 * inizializza l (PhoenixLineSensor) azzerando i valori di
 * soglia, misura, misura_max, misura_min, detect_flag e 
 * calibra_flag
 * OCCHIO a NON azzerare le variabili x ed y !
 **/
void PhoenixLineSensor_init(PhoenixLineSensor* l);

/**
 * Esegue la lettura del sensore, se la flag di calibrazione
 * (calibra_flag) e' attiva, allora aggiorna anche
 * misura_min e misura_max secondo queste condizioni:
 * misura < misura_min ? => misura_min = misura
 * misura > misura_max ? => misura_max = misura
 *
 * In oltre se la lettura e' maggiore della soglia
 * allora imposta ad 1 lo status (detect_flag)
 **/
void PhoenixLineSensor_handle(PhoenixLineSensor* l);

/**
 * imposta la variabile calibra_flag di l (PhoenixLineSensor)
 * pari a 1
 **/
void PhoenixLineSensor_startCalib(PhoenixLineSensor* l);

/**
 * imposta la variabile calibra_flag di l (PhoenixLineSensor)
 * pari a 0 
 * Poi imposta soglia secondo la formula:
 * soglia = (misura_max + misura_min) / 2
 * Poi azzera anche misura_min e misura_max
 **/
void PhoenixLineSensor_stopCalib(PhoenixLineSensor* l);

/**
 * restituisce il valore di detect_flag
 **/
uint8_t PhoenixLineSensor_getStatus(PhoenixLineSensor* l);

/**
 * imposta la variabile  detect_flag di l (PhoenixLineSensor)
 * pari a 0
 **/
void PhoenixLineSensor_reset(PhoenixLineSensor* l);
