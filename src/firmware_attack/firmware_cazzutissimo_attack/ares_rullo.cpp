
#include "ares_rullo.h"

PhoenixJoint solenoide = {
    pin_dira : 28,
    pin_dirb : 29,
    pin_pwm : 5, 
    direzione : 0 ,
    velocita : 0
};

void PhoenixSolenoide_init()
{
    PhoenixJoint_init(&solenoide);
}

void PhoenixSolenoide_start()
{
    PhoenixJoint_setSpeed(&solenoide, SOLENOIDE);
    PhoenixJoint_handle(&solenoide);
}

void PhoenixSolenoide_stop()
{
    PhoenixJoint_setSpeed(&solenoide, 0);
    PhoenixJoint_handle(&solenoide);
}

