/**
 * phoenix_imu.h
 **/

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "bno055.h"


typedef struct {
  BNO055* imu;
  double heading_attuale;
  double heading_target;
  double heading_offset;
  double errore;
  double output_pid;
  double errore_prec;

  double dt; //delta tempo
  double idt; //inverso delta tempo
  double sum_i; //sommatoria integrale
  int max_i; //massimo valore di sum_i
  int max_output;

  double kp;
  double ki;
  double kd;
}PhoenixImu;

/**
 * 
 * Inizializza la struttura m (PhoenixImu*) tramite la seguente procedura:
 * azzera heading_attuale, heading_target, heading_offset, errore, errore_pid
 * Inizializza imu (BNO055*) nel seguente modo:
 * 1) imposta imu->i2c_addr uguale a BNO055_I2C_ADDR
 * 2) imposta imu->op uguale a NDOF
 * 3) imposta imu->invert_heading uguale a 1
 * 4) lancia la funzione BNO055_init(m->imu)
 * 5) Se la funzione restituisce un valore diverso da 0
 *    allora bloccare l'inizializzazione e ritornare -1
 **/
uint8_t PhoenixImu_init(PhoenixImu* m);

/**
 * Esegue la funzione BNO055_handle(m->imu) per aggiornare
 * lo stato della periferica, sucessivamente assegna ad
 * heading_attuale, il valore di eul_heading di imu (accedi ad imu per
 * recuperare il valore).
 *
 * Successivamente calcola:
 * 1) errore pari a heading_target - (heading_attuale+heading_offset)
 * 2) errore_pid : ANCORA NON LO POTETE FARE
 *
 *
 * Piccola considerazione:
 * Se il modulo BNO055 ha una frequenza di risposta di 
 * 100 Hz (10mS) e in un secondo il loop viene eseguito circa
 * 30.000-35.000 volte (35 kHz o 28uS a loop), è conveniente
 * chiamare continuamente PhoenixImu_handle ? oppure
 * è più conveniente chiamarla solo ogni 10mS attraverso
 * un timer ? :) Nella prossima puntata...
 **/
void PhoenixImu_handle(PhoenixImu* m);

/**
 * Imposta heading_offset pari ad os
 **/
void PhoenixImu_setOffset(PhoenixImu* m, double os);

/**
 * Imposta heading_target pari a t
 **/
void PhoenixImu_setTarget(PhoenixImu* m, double t);
