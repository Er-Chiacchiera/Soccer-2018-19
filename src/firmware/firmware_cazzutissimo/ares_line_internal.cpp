/**
 * phoenix_line_internal.cpp
 **/

#include "ares_line_internal.h"


// PER FRANCESCO:
// Togli il blocco di commenti qui sotto
// x attivare la sezione relativa all'ADS1015

#include "Adafruit_ADS1015.h"
#define NUM_ADC 4
#define LINE_ADC_ADDR_FRONT  0
#define LINE_ADC_ADDR_LEFT   1
#define LINE_ADC_ADDR_RIGHT  2
#define LINE_ADC_ADDR_BACK   3
static Adafruit_ADS1015 line_adc[NUM_ADC] = {
 Adafruit_ADS1015(LINE_ADC_ADDR_FRONT),
 Adafruit_ADS1015(LINE_ADC_ADDR_LEFT),
 Adafruit_ADS1015(LINE_ADC_ADDR_RIGHT),
 Adafruit_ADS1015(LINE_ADC_ADDR_BACK)
};



/**
 * inizializza l (PhoenixLineSensor) azzerando i valori di
 * soglia, misura, misura_max, misura_min, detect_flag e 
 * calibra_flag
 * OCCHIO a NON azzerare le variabili x ed y !
 **/
void PhoenixLineSensor_init(PhoenixLineSensor* l) {
  /**
   * Per Francesco:
   * In questa funzione dovrai anche inizializzare l'adc relativo
   * al sensore. Puoi farlo tramite la funzione:
   * line_adc[l->adc_addr].begin()
   **/
  // Da completare...
  l->soglia = 0;
  l->misura = 0;
  l->misura_max = 0;
  l->misura_min = 0;
  l->detect_flag = 0;
  l->calibra_flag = 0;
  line_adc[l->adc_addr].begin();
  return;
}

/**
 * Esegue la lettura del sensore, se la flag di calibrazione
 * (calibra_flag) e' attiva, allora aggiorna anche
 * misura_min e misura_max secondo queste condizioni:
 * misura < misura_min ? => misura_min = misura
 * misura > misura_max ? => misura_max = misura
 *
 *In oltre se la lettura e' maggiore della soglia
 * allora imposta ad 1 lo status (detect_flag)
 **/
void PhoenixLineSensor_handle(PhoenixLineSensor* l) {
  /**
   * ASSOLUTAMENTE DA LEGGERE:
   *
   * Per Francesco:
   * Puoi effettuare la lettura del sensore accedendo all'array
   * di ADS1015 (line_adc) nell'indice l->adc_addr e scrivendo
   * il seguente comando:
   * lettura = line_adc[d->adc_addr].readADC_SingleEnded(d->adc_idx);
   *
   * Per Sara:
   * Puoi effettuare la lettura del sensore tramite una lettura analogica
   * al pin: l->pin_reading
   **/
    double lettura = 0;
    lettura = line_adc[l->adc_addr].readADC_SingleEnded(l->adc_idx);
    
    if(l->calibra_flag = 1)
    {
      if(l->misura < l->misura_min)
      {
        l->misura_min = l->misura;
      }
      else if(l->misura > l->misura_max)
      {
        l->misura_max = l->misura;
      }
    }
  // Da completare...
  return;
}

/**
 * imposta la variabile calibra_flag di l (PhoenixLineSensor)
 * pari a 1
 **/
void PhoenixLineSensor_startCalib(PhoenixLineSensor* l) {
  l->calibra_flag = 1;
  // Da completare...
  return;
}

/**
 * imposta la variabile calibra_flag di l (PhoenixLineSensor)
 * pari a 0 
 * Poi imposta soglia secondo la formula:
 * soglia = (misura_max + misura_min) / 2
 * Poi azzera anche misura_min e misura_max
 **/
void PhoenixLineSensor_stopCalib(PhoenixLineSensor* l) {
  l->calibra_flag= 0;
  l->soglia = (l->misura_max + l->misura_min) / 2;
  l->misura_min = 0;
  l->misura_max = 0;
  // Da completare...
  return;
}

/**
 * restituisce il valore di detect_flag
 **/
uint8_t PhoenixLineSensor_getStatus(PhoenixLineSensor* l) {
  // Da completare...
  return l->detect_flag;
}

/**
 * imposta la variabile  detect_flag di l (PhoenixLineSensor)
 * pari a 0
 **/
void PhoenixLineSensor_reset(PhoenixLineSensor* l) {
  l->detect_flag = 0;
  // Da completare...
  return;
}
