#pragma once

#include "ares_globals.h"  //includo libreria

Adafruit_ADS1015 line_adc[4] {  //dichiaro i sensori di linea 
    Adafruit_ADS1015(0),
    Adafruit_ADS1015(1),
    Adafruit_ADS1015(2),
    Adafruit_ADS1015(3)
};

