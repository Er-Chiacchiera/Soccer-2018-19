
#include <Arduino.h>
#include "ares_bumper.h"

/**
 *  inizializza lettura_bumper e detect_bumper = 0
 **/
void Bumper_init(Bumper * b){
    b->lettura_bumper = 0;
    b->detect_bumper = 0;
}
/**
 * Fa una lettura digitale sul pin del bumper e se:
 * - lettura_bumper = 1 allora detect_bumper = 1
 * - lettura_bumper = 0 allora detect_bumper = 0
 **/
void Bumper_handle(Bumper * b){
    b->lettura_bumper = digitalRead(b->pin_bumper);
    if(b->lettura_bumper == 1){
        b->detect_bumper = 1;
    }
    else{
        b->detect_bumper = 0;
    }
}
/**
 * imposta lettura_bumper e detect_bumper = 0  
 **/
void Bumper_reset(Bumper * b){
    b->lettura_bumper = 0;
    b->detect_bumper = 0;
}