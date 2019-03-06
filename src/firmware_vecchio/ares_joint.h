//ok
#pragma once 

#include <Arduino.h> 
#include "ares_globals.h"  
//#include "ares_status.h"   // <-----

class Joint {  //creo una classe di nome "Joint"
    uint8_t pin_pwm;
    uint8_t pin_dira;        //creo delle variabili 
    uint8_t pin_dirb;        // <-------
                             // <-------
    uint8_t pwm;
    uint8_t dir;
 
 //riferimento aquisizione pin:
 /*
 pins[0] -> pwm    
 pins[1] -> dira
 pins[2] -> dirb 
 */

    public:
    Joint();  //richiamo joint                                           
    void init(uint8_t* pins);       //richiamo una funzione di nome "init" con un puntatore di nome "pins" 
    void setSpeed(int16_t speed);   //richiamo una funzione con variabile "speed" a 2 byte 
    void handle();                  //richiamo una funzione
};
