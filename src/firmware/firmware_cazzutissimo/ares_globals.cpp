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
  velocita : 0,
  pwm : 0
  },
  {// Joint 1
  pin_dira : 24, //24
  pin_dirb : 25, //25
  pin_pwm : 3,  //3
  direzione : 0,
  velocita : 0,
  pwm : 0
  },
  {// Joint 2
  pin_dira : 26,  
  pin_dirb : 27, 
  pin_pwm : 4,   
  direzione : 0,
  velocita : 0,
  pwm : 0
  }
};


PhoenixDrive drive;

PhoenixLineSensor line_sensors[] = {   // sen = y
  {
  x : 0.97,
  y : 0.23,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 0
  },
  {
  x : 0.5,
  y : 0,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 1
  },
  {
  x : 0.7,
  y : 0.7,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 0,
  adc_idx : 2
  },
  //sensor_2
  {
  x : -0.7,
  y : 0.7,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 0
  },
  {
  x : 0.5,
  y : -0.86,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 1
  },
  {
  x : -0.97,
  y : 0.23,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 2
  },
  //sensor_3
  {
  x : 0,
  y : 0,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 0
  },
  {
  x : 0,
  y : 0,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 1
  },
  {
  x : 0,
  y : 0,
  soglia : 0,
  soglia_black : 0,
  misura : 0,
  misura_min : 65535,
  misura_max : 0,
  detect_flag : 0,
  detect_flag_black : 0,
  calibra_flag : 0,
  adc_addr : 2,
  adc_idx : 2
  }
};

Adafruit_ADS1015 line_adc;

PhoenixLineHandler line_handler;

BNO055 dev_bno055;
PhoenixImu imu = {
  imu : &dev_bno055,
  heading_attuale : 0,
  heading_target : 0,
  heading_offset : 0,
  errore : 0,
  output_pid : 0,
  errore_prec : 0,
  x : 0,
  y : 0,
  dt : 0.001,
  idt : 1000,
  sum_i: 0,
  max_i: 180,
  max_output: 180,
  kp : 9,   //9
  ki : 40,  //40
  kd : 0
};

PhoenixCamera _pixy = {
  ball_detection : 0,
  door_detection : 0,
  ball_x : 0,
  ball_y : 0,
  ball_w : 0,
  ball_h : 0,
  door_x : 0,
  door_y : 0,
  door_w : 0,
  door_h : 0,
  ball_age : 0,
  door_age : 0,
  area_ball : 0,
  area_door : 0,
  kp : 1.3,
  ki : 0.4,
  kd : 0,
  errore : 0,
  errore_prec : 0,
  idt : 60,
  sum_i : 0,
  dt : 0.0167,
  max_i : 180,
  output_pid_camera : 0,
  max_output : 180
};

