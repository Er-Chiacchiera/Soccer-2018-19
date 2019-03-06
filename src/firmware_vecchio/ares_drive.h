#pragma once 
#include <Arduino.h>
#include "ares_joint.h"   //includo delle librerie

typedef struct{  //creo una struttura per i dati  dei motori
    double x;
    double y;
    uint8_t pins[3];

} JointDati;

typedef struct{  //creo una struttura per i controlli dei motori
    int16_t speed;
    uint8_t mode;
} JointControlli;

class HolonomicDrive {  //creo una classe per dichiarare delle variabili che serviranno da puntatori 
  Joint* joints;        //nelle strutture create passandogli i vari parametri e dichiarando delle 
  JointParams* params;  //funzioni da utilizzare
  JointControl* control;
  
  public:
  HolonomicDrive();
  void init(Joint* joints, JointParams* params,
            JointControl* control);
  void move(double x, double y, double theta);
  void handle();
};