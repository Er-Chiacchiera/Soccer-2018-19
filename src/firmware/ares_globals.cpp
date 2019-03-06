/**
 * phoenix_globals.cpp
 **/

#include "ares_globals.h"

PhoenixJoint joints[NUM_JOINTS] = {
  {// Joint 0
  pin_dira : 22, 
  pin_dirb : 23,  
  pin_pwm : 2,   
  direzione : 0,
  velocita : 0
  },
  {// Joint 1
  pin_dira : 24, 
  pin_dirb : 25,
  pin_pwm : 3,
  direzione : 0,
  velocita : 0
  },
  {// Joint 2
  pin_dira : 26,
  pin_dirb : 27,
  pin_pwm : 4,
  direzione : 0,
  velocita : 0
  }
};


PhoenixDrive drive;

PhoenixLineSensor line_sensors[NUM_LINE_SENSORS] = {
  {// Sensore 0
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0,
  pin_reading: 0
  },
  {// Sensore 1
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0,
  pin_reading: 0
  },
  {// Sensore 2
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0,
  pin_reading: 0
  },
  {// Sensore 3
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0,
  pin_reading: 0
  },
  {// Sensore 4
  x : 0,
  y : 0,
  soglia : 0,
  misura : 0,
  misura_min : 0,
  misura_max : 0,
  detect_flag : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0,
  pin_reading: 0
  }
};
PhoenixLineHandler line_handler;

BNO055 dev_bno055;
PhoenixImu imu;
