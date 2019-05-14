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

  double kp;
  double ki;
  double kd;
  double errore;
  double errore_prec;
  double dt;
  double idt;
  double sum_i;
  double max_i;
  double output_pid_joint;
  double max_output;
  double speed_encoder;
  double velocita_desiderata;
  double velocita_misurata;
  double prev_ticks;
  double num_ticks;
}PhoenixJoint;


void PhoenixJoint_init(PhoenixJoint* j);
void PhoenixJoint_setSpeed(PhoenixJoint* j, int velocita);
void PhoenixJoint_handle(PhoenixJoint* j);