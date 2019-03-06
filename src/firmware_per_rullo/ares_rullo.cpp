
#include "ares_rullo.h"

void PhoenixRullo_init(PhoenixRullo*j)
{
    digitalWrite(j->pin_dir_a_r, 0);
    digitalWrite(j->pin_dir_b_r, 0);
    analogWrite(j->pin_pwm_r, 0);

    digitalWrite(j->pin_dir_a_r, OUTPUT);
    digitalWrite(j->pin_dir_b_r, OUTPUT);
    analogWrite(j->pin_pwm_r, OUTPUT);
}

void PhoenixRullo_setSpeed(PhoenixRullo*j, int velocitarullo)
{
    if(velocitarullo >= 0)
    {
        j->velocitar = velocitarullo;
        j->direzioner = 0;
    }
    else
    {
        j->velocitar = - velocitarullo;
        j->direzioner = 1;
    }
    if(j->velocitar > 255)
    {
        j->velocitar = 255;
    }
}

void PhoenixRullo_handle(PhoenixRullo*j)
{
    digitalWrite(j->pin_dir_a_r, j->direzioner);
    digitalWrite(j->pin_dir_b_r, !j->direzioner);
    analogWrite(j->pin_pwm_r, j->velocitar);
}
