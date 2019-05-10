
#include "ares_rullo.h"

PhoenixJoint rullo = {
    pin_dira : 28,
    pin_dirb : 29,
    pin_pwm : 5, 
    direzione : 0 ,
    velocita : 0
};

void PhoenixRullo_init()
{
    PhoenixJoint_init(&rullo);
}

void PhoenixRullo_start()
{
    PhoenixJoint_setSpeed(&rullo, -SPEED_RULLO);
    PhoenixJoint_handle(&rullo);
}

void PhoenixRullo_stop()
{
    PhoenixJoint_setSpeed(&rullo, 0);
    PhoenixJoint_handle(&rullo);
}

