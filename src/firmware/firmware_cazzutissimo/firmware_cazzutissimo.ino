/**
   firmware.ino
-----------------------------------------------------
**/

#include "ares_params.h"
#include "ares_globals.h"
#include "ares_joints.h"
#include "ares_drive.h"
#include "ares_line_internal.h"
#include "ares_line.h"
#include "ares_imu.h"
#include "ares_timer.h"
#include "ares_rullo.h"
#include "ares_encoders.h"
#include "ares_eeprom.h"
#include "ares_pixy.h"

#define ENABLE_LINE_CALIB 0



void TestEncoderFn() {
  static volatile int state=0;
  static volatile int joint=0;
  switch(state) {
    case 0:
    PhoenixJoint_setSpeed(&joints[joint], 100);
    PhoenixJoint_handle(&joints[joint]);
    break;
    case 1:
    PhoenixJoint_setSpeed(&joints[joint], 0);
    PhoenixJoint_handle(&joints[joint]);
    joint = (joint+1)%3;
    break;
  }
  state = (state+1)%2;
}




void setup() {
  Serial.begin(9600);
  Serial.println("Serial initialized...");
  for(int i=0;i<NUM_JOINTS;++i) {
    PhoenixJoint_init(&joints[i]);
  }
  Serial.println("Joint inizialized...");

  PhoenixDrive_init(&drive, joints);
  /*
  if(PhoenixImu_init(&imu)==0)
  {
    Serial.println("IMU inizialized...");
  }
  else
  {
    Serial.println("IMU error");
  }
  delay(1000);
  PhoenixImu_handle(&imu);
  PhoenixImu_setOffset(&imu, imu.heading_attuale);*/
 //Encoder_init();
 
 /*while(PhoenixImu_init(&imu)) {
  delay(500);
  Serial.println("non funziona");
 }
 Serial.println("Mo funziona");*/


 /*PhoenixRullo_init();
 Serial.println("Rullo inizialized...");*/
/*
 for(int i=0;i<NUM_LINE_SENSORS;++i) {
    PhoenixLineSensor_ADCBegin(&line_sensors[i]);
    PhoenixLineSensor_init(&line_sensors[i]);
    PhoenixLineSensor_startCalib(&line_sensors[i]);
    PhoenixLineSensor_handle(&line_sensors[i]);
    PhoenixLineSensor_stopCalib(&line_sensors[i]);
  }
  Serial.println("Line Sensors initialized...");
  PhoenixLineHandler_init(&line_handler, line_sensors);
  Serial.println("Line Handler initialized...");
  
  PhoenixEeprom_init();
  
  #if ENABLE_LINE_CALIB == 1 
  PhoenixLineHandler_startCalib(&line_handler);
  PhoenixDrive_setSpeed(&drive, 0,0,1);
  PhoenixDrive_handle(&drive);
  uint16_t start = millis();
  while(1){
    PhoenixLineHandler_handle(&line_handler);
    if(millis() - start > 10000){
      break; 
    }
  }
  PhoenixDrive_setSpeed(&drive, 0,0,0);
  PhoenixDrive_handle(&drive);
  PhoenixLineHandler_stopCalib(&line_handler);
  PhoenixEeprom_storeLineSensor();
  while(1);
  #endif 
  PhoenixEeprom_loadLineSensor();*/
  
  struct Timer* t1_fn=Timer_create(1000/60, 
  PhoenixCamera_handle, (void*)&_pixy);
  Timer_start(t1_fn);
  Timer_init();
  PhoenixCamera_init(&_pixy);
  Serial.println("Camera initialized...");
}

void Test_connections(void){
  PhoenixJoint_handle(&joints[0]);
  PhoenixJoint_setSpeed(&joints[0], 255); //(ALTO A DESTRA)
  PhoenixJoint_setSpeed(&joints[0], 0);
  PhoenixJoint_handle(&joints[0]);
  PhoenixJoint_handle(&joints[1]);
  PhoenixJoint_setSpeed(&joints[1], 255); //(ALTO A SINISTRA)
  PhoenixJoint_setSpeed(&joints[1], 0);
  PhoenixJoint_handle(&joints[1]);
  PhoenixJoint_handle(&joints[2]);
  PhoenixJoint_setSpeed(&joints[2], 255); //(BASSO)
  PhoenixJoint_setSpeed(&joints[1], 0);
  PhoenixJoint_handle(&joints[2]);
}
  
void Test_ImuPid(void){
  PhoenixImu_handle(&imu);
  PhoenixDrive_setSpeed(&drive , 0,1,-imu.output_pid/180);
  PhoenixDrive_handle(&drive);
  Serial.print(imu.heading_target);
  Serial.print("\t");
  Serial.print(imu.sum_i);
  Serial.print("\t");
  Serial.print(imu.output_pid/180);
  Serial.println("\t");
  delay(10);
}

void Test_LineInternal(void){
  for(int i=0;i<6;i++){
  //Serial.print(PhoenixLineSensor_getStatus(&line_sensors[i]));
  PhoenixLineSensor_handle(&line_sensors[i]);
  //Serial.print(" ");

  Serial.print(line_sensors[i].misura); 
  Serial.print(" ");
  /*
  Serial.print(line_sensors[i].soglia);
  Serial.print(" ");*/
  }
  Serial.println();
}

void Test_Line(void){
  PhoenixLineHandler_handle(&line_handler);
  Serial.print(PhoenixLineHandler_getStatus(&line_handler));
  Serial.print(" ");
  Serial.print(PhoenixLineHandler_getEscapeX(&line_handler));
  Serial.print(" ");
  Serial.print(PhoenixLineHandler_getEscapeY(&line_handler));
  Serial.println();
  PhoenixLineHandler_reset(&line_handler);
}

void Test_Rullo(void){
  PhoenixRullo_start();
  PhoenixDrive_setSpeed(&drive, 0,1,0);
  PhoenixDrive_handle(&drive);
}

void Test_RulloSingleStart(void){
  PhoenixRullo_start();
}

void Test_Encoder(void){
  Encoder_sample();
  Serial.print(Encoder_getValue(0));
  Serial.print("\t");
  Serial.print(Encoder_getValue(1));
  Serial.print("\t");
  Serial.print(Encoder_getValue(2));
  Serial.println("\t");
}

void Test_ADC(void){
  for(int i=0;i<NUM_LINE_SENSORS;++i){
    Test_ADCBegin(&line_sensors[i]);
  }
}

void Test_EscapeLine(void){
  double x=0;
  double y=0;
  double t=0;

  PhoenixImu_handle(&imu);
  t=-imu.output_pid/180.0;
  PhoenixLineHandler_handle(&line_handler);
  if(line_handler.escape_flag == 1){
    x=line_handler.escape_x;
    y=line_handler.escape_y;
  }
  else{
    x=0;
    y=1;
  }
  
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
  Serial.println(PhoenixLineHandler_getStatus(&line_handler));
}

void Test_pixy(void){
  int Xmin = 70;
  int Xmax = 200;
  int minArea = 0;
  int maxArea = 0;
  double x = _pixy.ball_x;
  double y = _pixy.ball_y;
  while(millis()<2000)
  {
    unsigned int area = _pixy.area_ball;
    maxArea = area + 550;
    minArea = area - 550;
  }
  if(PhoenixCamera_getBallStatus(&_pixy)){
    unsigned int new_area = _pixy.area_ball;
    if(x < Xmin){
      PhoenixDrive_setSpeed(&drive, -1,0,0);
      PhoenixDrive_handle(&drive);
    }
    else if(x > Xmax){
      PhoenixDrive_setSpeed(&drive, 1,0,0);
      PhoenixDrive_handle(&drive);
    }
    else if(new_area < minArea){
      PhoenixDrive_setSpeed(&drive, 0,1,0);
      PhoenixDrive_handle(&drive);
    }
    else if(new_area > maxArea){
      PhoenixDrive_setSpeed(&drive, 0,1,0);
      PhoenixDrive_handle(&drive); 
    }
    /*else{
      PhoenixDrive_setSpeed(&drive, 0,0,0);
      PhoenixDrive_handle(&drive);
    }*/
  }
  else{
    PhoenixDrive_setSpeed(&drive, 0,0,0);
    PhoenixDrive_handle(&drive);
  }

  }


/**
 * avanti = 0, 1, 0      per toccare la vel_max imposta a 2
 * indietro = 0, -1, 0
 * destra = 1, 0, 0
 * sinistra -1, 0, 0
 */


void loop() {
  Test_pixy();
}


