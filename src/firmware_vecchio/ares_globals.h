#pragma once

#include <Adafruit_ADS1015.h>   //includo librerie 
#include <Arduino.h>
#define NUM_LINEDETECTORS 16   //dichiaro il numero di sensori 

extern Adafruit_ADS1015 line_adc[4];   //richiamo funzioni dalle librerie di Arduino
extern AresLineDetector line_detectors[NUM_LINEDETECTORS];
