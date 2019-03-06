
#pragma once
#include <Arduino.h>


typedef struct{
    uint8_t pin_dir_a_r;
    uint8_t pin_dir_b_r;
    uint8_t pin_pwm_r;

    uint8_t direzioner;
    uint8_t velocitar;
}PhoenixRullo;

void PhoenixRullo_init(PhoenixRullo* j);
void PhenixRullo_setSpeed(PhoenixRullo* j, int velocitarullo);
void PhenixRullo_handle(PhoenixRullo*j);

