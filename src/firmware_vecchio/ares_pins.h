#pragma once

#include "ares_globals.h"
#include "ares_drive.h"
#include "ares_joint.h"

JointDati dati[NUM_MOTORS] = {
// dati[0] motore 1
  {
    ._x = 0,
    ._y = 0,
    .pins = {10,11,12}  //pin motore 1
  },
  // dati[1] motore 2
  {
    ._x = 0,
    ._y = 0,
    .pins = {3,4,5}   //pin motore 2
  },
  // dati[2] motore 3
  {
    ._x = 0,
    ._y = 0,
    .pins = {21,22,23}  //pin motore 3
  }
};

Joint joint[NUM_MOTORS] ;


JointControlli controlli[NUM_MOTORS] = {
  
  {
    .speed = 0,
    .mode = 0
  },
  {
    .speed = 0,
    .mode = 0
  },
  {
    .speed = 0,
    .mode = 0
  }
  
};
