/**
 * phoenix_line_internal.cpp
 **/

#include "ares_line_internal.h"
#include "Adafruit_ADS1015.h"

#define NUM_ADC 3

#define LINE_ADC_I2C_ADDR_0 0x48
#define LINE_ADC_I2C_ADDR_1 0x49
#define LINE_ADC_I2C_ADDR_2 0x4A

#define LINE_ADC_ADDR_J0 0
#define LINE_ADC_ADDR_J1 1
#define LINE_ADC_ADDR_J2 2

static Adafruit_ADS1015 line_adc[NUM_ADC] = {
 Adafruit_ADS1015(LINE_ADC_I2C_ADDR_0),
 Adafruit_ADS1015(LINE_ADC_I2C_ADDR_1),
 Adafruit_ADS1015(LINE_ADC_I2C_ADDR_2),
};

void PhoenixLineSensor_ADCBegin(PhoenixLineSensor * l){
  for(int i=0;i<NUM_ADC;i++){
    line_adc[i].begin();
  }
  return;
}

void Test_ADCBegin(PhoenixLineSensor * l){
    int16_t adc0, adc1, adc2;

    adc0 = line_adc[0].readADC_SingleEnded(0);
    adc1 = line_adc[1].readADC_SingleEnded(1);
    adc2 = line_adc[2].readADC_SingleEnded(2);
    Serial.print("AIN0: "); Serial.println(adc0);
    Serial.print("AIN1: "); Serial.println(adc1);
    Serial.print("AIN2: "); Serial.println(adc2);
    Serial.println(" ");
}

/**
 * inizializza l (PhoenixLineSensor) azzerando i valori di
 * soglia, misura, misura_max, detect_flag e 
 * calibra_flag
 * OCCHIO a NON azzerare le variabili x ed y !
 * UPDATE: misura_min deve essere inizializzato a 65535
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
  l->misura_min = 65535;
  l->detect_flag = 0;
  l->calibra_flag = 0;
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
    l->misura = lettura;
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
 * Poi azzera misura_max e imposta misura_min pari a 65535
 **/
void PhoenixLineSensor_stopCalib(PhoenixLineSensor* l) {
  l->calibra_flag= 0;
  l->soglia = (l->misura_max + l->misura_min) / 2;
  l->misura_min = 65535;
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
