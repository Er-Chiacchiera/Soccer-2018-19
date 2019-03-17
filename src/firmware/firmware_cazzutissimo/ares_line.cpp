/**
 * phoenix_line.cpp
 **/

#include "ares_line.h"

// Funzioni utili per lavorare con la maschera.
uint8_t mask_read(uint16_t* mask, uint8_t index) {
  return *mask & (0x1<<index)!=0;
}

void mask_setBit(uint16_t* mask, uint8_t index) {
  *mask |= (0x1<<index); 
}

void mask_clearBit(uint16_t* mask, uint8_t index) {
  *mask &= ~(0x1<<index);
}


/**
 * inizializza d (PhoenixLineHandler) azzerando i valori di
 * escape_flag, escape_x ed escape_y ed impostando 
 * la variabile escape_ttl pari a ESCAPE_TTL
 * Poi assegna la variabile line_sensors = s 
 **/
void PhoenixLineHandler_init(PhoenixLineHandler* d, PhoenixLineSensor* s) {
  d->escape_flag = 0;
  d->escape_x = 0;
  d->escape_y = 0;
  d->escape_ttl = ESCAPE_TTL;
  d->line_sensors = s;
  return;
}

/**
 * Parte difficile :)
 *
 * lancia la funzione PhoenixLineSensor_handle su tutti i sensori
 * presenti nell'array d->line_sensors
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
void PhoenixLineHandler_handle(PhoenixLineHandler* d) {
  for(int a=0;a<NUM_LINE_SENSORS;a++){
    PhoenixLineSensor_handle(&d->line_sensors[a]);
  }
  if(d->calib_flag == 1){
    return;
  }
  for(int b=0;b<NUM_LINE_SENSORS;b++)
  {
    if(mask_read(&d->mask,b) == 0)
    {
      if(PhoenixLineSensor_getStatus(&d->line_sensors[b]) == 1)
      {
        mask_setBit(&d->mask, b); 
        d->escape_x = d->escape_x - d->line_sensors[b].x;  
        d->escape_y = d->escape_y - d->line_sensors[b].y;  
        d->escape_flag = 1;
        d->escape_ttl = ESCAPE_TTL;
      }
    }
  }
  if(d->escape_flag == 1)
  {
    d->escape_ttl = d->escape_ttl - 1;
  }
  if(d->escape_ttl == 0)
  {
    PhoenixLineHandler_reset(d);
  }
}



/**
 * restituisce il valore di escape_flag
 **/
uint8_t PhoenixLineHandler_getStatus(PhoenixLineHandler* d) {
  return d->escape_flag;
}

/**
 * restituisce il valore di escape_x
 **/
double PhoenixLineHandler_getEscapeX(PhoenixLineHandler* d) {
  return d->escape_x;
}

/**
 * restituisce il valore di escape_y
 **/
double PhoenixLineHandler_getEscapeY(PhoenixLineHandler* d) {
  return d->escape_y;
}

/**
 * deve azzerare la variabile escape_flag, escape_x, escape_y e 
 * mask.
 * Per ogni sensore poi, bisogna lanciare la funzione 
 * PhoenixLineSensor_reset
 **/
void PhoenixLineHandler_reset(PhoenixLineHandler* d) {
  d->escape_flag = 0;
  d->escape_x = 0;
  d->escape_y = 0;
  d->mask = 0;          
  for(int i=0;i<NUM_LINE_SENSORS;i++)
  {
    mask_clearBit(&d->mask, i); 
    PhoenixLineSensor_reset(&d->line_sensors[i]);
  }
}

void PhoenixLineHandler_startCalib(PhoenixLineHandler* d){
  d->calib_flag = 1;
  for(int i=0;i<NUM_LINE_SENSORS;++i){
    PhoenixLineSensor_startCalib(&d->line_sensors[i]);
  }
}

/**
 * azzera calib_flag e lancia la funzione PhoenixLineSensor_stopCalib
 * per ogni sensore in line_sensors
 **/
void PhoenixLineHandler_stopCalib(PhoenixLineHandler* d) {
  d->calib_flag = 0;
  for(int i=0;i<NUM_LINE_SENSORS;++i){
    PhoenixLineSensor_stopCalib(&d->line_sensors[i]);
  }
  return;
}