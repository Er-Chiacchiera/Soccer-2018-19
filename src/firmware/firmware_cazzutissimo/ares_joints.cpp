
/**
 * phoenix_joints.cpp
 **/
#include "ares_joints.h"
#include "ares_encoders.h"
#include "utils.h"
/**
 * Azzera i valori di direzione e velocita,
 * inizializza i pin di dira, dirb e pwm 
 * sulla piattaforma di Arduino
 **/
void PhoenixJoint_init(PhoenixJoint* j) {
  pinMode(j->pin_pwm, OUTPUT);
  analogWrite(j->pin_pwm, 0);

  pinMode(j->pin_dira, OUTPUT);
  digitalWrite(j->pin_dira, 0);

  pinMode(j->pin_dirb, OUTPUT);
  digitalWrite(j->pin_dirb, 0);
}

/**
 * Imposta direzione e velocita di j (PhoenixJoint)
 * dato il parametro velocita.
 * direzione = segno(velocita) [0 se positivo, 1 se negativo]
 * velocita = modulo(velocita) [0, 255]
 */
void PhoenixJoint_setSpeed(PhoenixJoint* j, int velocita) {
  j->velocita_desiderata = velocita;
  return;
}

/**
 * Comunica alla piattaforma di Arduino,
 * i nuovi stati sui pin dira, dirb e pwma
 * tramite le funzioni di 
 * digitalWrite
 * analogWrite
 */
void PhoenixJoint_handle(PhoenixJoint* j) {
  Encoder_sample();
  j->prev_ticks = j->speed_encoder;
  j->speed_encoder = Encoder_getValue(j->num_ticks);
  j->velocita_misurata = j->speed_encoder - j->prev_ticks;
  j->errore = j->velocita_desiderata - j->velocita_misurata;
  j->errore = cconstraint(j->errore, 255, -255);
  j->e_p = j->errore * j->kp;
  j->e_d = j->kd*(j->errore - j->errore_prec)*j->idt;
  j->sum_i += j->ki*j->errore*j->dt;
  j->sum_i = clamp(j->sum_i, j->max_i);
  j->output_pid_joint = j->e_p + j->e_d + j->sum_i;
  j->output_pid_joint = clamp(j->output_pid_joint, j->max_output);
  j->errore_prec = j->errore;

  int16_t speed = j->output_pid_joint;

  if(speed < 0){
    j->velocita = - speed;
    j->direzione = 1;
  }
  else{
    j->velocita = speed;
    j->direzione = 0;
  }
  if(j->velocita < 10){
    j->velocita = 0;
  }
  digitalWrite(j->pin_dira, j->direzione);
  digitalWrite(j->pin_dirb, !j->direzione);
  analogWrite(j->pin_pwm, j->velocita);
  return;
}
