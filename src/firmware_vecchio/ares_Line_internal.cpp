#pragma once

#include "ares_Line_internal.h"      //includo delle librerie
#include <Adafruit_ADS1015.h>     
#include "ares_globals.h"
#include <math.h>

void LineDetector_init(LineDetector* d) {   //creo una funzione che inizializza le variabili
    d->rilevato = 0;                        //rilevato, soglia, valore letto impostandole tutte a 0
    d->valore_letto = 0;
    d->soglia = 0;

    line_adc[d->adc_addr].begin();  //inserisco i dati nella funzione di begin()
}
int LineDetector_handle(LineDetector* d){
    d->valore_letto = line_adc[d->adc_addr].readADC_SingleEnded(d->adc_idx);  
    if(d->valore_letto > d->soglia)
    {
        d->rilevato = 1;            //creo una funzione che legge lo stato di ogni sensore e aggiorna
        return 0;                   //la variabile che contiene il dato di rilevazione
    }
}
void LineDetector_reset(LineDetector* d){   //creo una funzione che resetta le variabili 
    d->rilevato = 0;                        //rilevato e valore_letto a 0
    d->valore_letto = 0;
}