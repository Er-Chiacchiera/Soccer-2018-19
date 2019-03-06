#pragma once 
#include <Arduino.h>

typedef struct {    //creo una struttura che contiene le 3 variabili usate per i sensori di linea
    uint16_t rilevato;
    uint16_t valore_letto;
    uint16_t soglia;

    uint8_t adc_addr;
    uint8_t adc_idx;
} LineDetector;

void LineDetector_init(LineDetector*);    //creo la funzione di init()
void LineDetector_handle(LineDetector*);  //creo la funzione di handle()
void LineDetector_reset(LineDetector*);   //creo la funzione di reset()
