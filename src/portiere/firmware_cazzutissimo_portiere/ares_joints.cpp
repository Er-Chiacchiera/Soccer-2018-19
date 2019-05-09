
/**
 * phoenix_joints.cpp
 **/
#include "ares_joints.h"
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
  if(velocita>= 0){
    j->velocita = velocita;
    j->direzione = 0;
  }
  else{
    j->velocita = - velocita;
    j->direzione = 1;
  }
  if(j->velocita > 255){
    j->velocita = 255;
  }
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
  if(j->velocita < 50){
    j->velocita = 0;
  }
  digitalWrite(j->pin_dira, j->direzione);
  digitalWrite(j->pin_dirb, !j->direzione);
  analogWrite(j->pin_pwm, j->velocita);
  return;
}
