/**
 * phoenix_joints.h
 **/

#pragma once
#include <Arduino.h>

typedef struct {
  uint8_t pin_dira;
  uint8_t pin_dirb;
  uint8_t pin_pwm;

  uint8_t direzione;
  uint16_t velocita;

  uint8_t pwm;
}PhoenixJoint;


void PhoenixJoint_init(PhoenixJoint* j);
void PhoenixJoint_setSpeed(PhoenixJoint* j, int velocita);
void PhoenixJoint_handle(PhoenixJoint* j);