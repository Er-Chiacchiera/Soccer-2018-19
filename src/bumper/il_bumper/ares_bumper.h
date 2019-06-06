
#include <stdio.h>
#include <Arduino.h>


typedef struct {

    int pin_bumper;
    int lettura_bumper;
    int detect_bumper;

} Bumper;

/**
 *  inizializza lettura_bumper e detect_bumper = 0
 **/
void Bumper_init(Bumper * b);
/**
 * Fa una lettura digitale sul pin del bumper e se:
 * - lettura_bumper = 1 allora detect_bumper = 1
 * - lettura_bumper = 0 allora detect_bumper = 0
 **/
void Bumper_handle(Bumper * b);
/**
 * imposta lettura_bumper e detect_bumper = 0  
 **/
void Bumper_reset(Bumper * b);


