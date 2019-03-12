/**
   
   firmware.ino

-----------------------------------------------------

   Copyright 2018 Emanuele Giacomini
   
   Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
   
       http://www.apache.org/licenses/LICENSE-2.0
   
   Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and limitations under the License.
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

  Encoder_init();
 
 /*while(PhoenixImu_init(&imu)) {
  delay(500);
  Serial.println("non funziona");
 }
 Serial.println("Mo funziona");*/

/*
 PhoenixRullo_init();
 Serial.println("Rullo inizialized...");*/


/*
 for(int i=0;i<NUM_LINE_SENSORS;++i) {
    PhoenixLineSensor_init(&line_sensors[i]);
  }
  Serial.println("Line Sensors initialized...");
  PhoenixLineHandler_init(&line_handler, line_sensors);
  Serial.println("Line Handler initialized...");*/
}

void Test_connections(){
  PhoenixJoint_handle(&joints[0]);
  PhoenixJoint_setSpeed(&joints[0], 255);
  //Serial.println("MOTORE 0 (ALTO A DESTRA)");
  delay(1000);
  PhoenixJoint_handle(&joints[1]);
  PhoenixJoint_setSpeed(&joints[1], 255);
  //Serial.println("MOTORE 1 (ALTO A SINISTRA)");
  delay(1000);
  PhoenixJoint_handle(&joints[2]);
  PhoenixJoint_setSpeed(&joints[2], 255);
  //Serial.println("MOTORE 0 (BASSO)");
  delay(1000);
}
  
void Test_ImuPid(){
  PhoenixImu_handle(&imu);
  PhoenixDrive_setSpeed(&drive , 0,0,-imu.output_pid/180);
  PhoenixDrive_handle(&drive);
  Serial.print(imu.heading_target);
  Serial.print("\t");
  Serial.print(imu.sum_i);
  Serial.print("\t");
  Serial.print(imu.output_pid/180);
  Serial.println("\t");
  delay(10);
}

void Test_Line(){
  for(int i=0;i<NUM_LINE_SENSORS;i++){
  PhoenixLineSensor_handle(&line_sensors[i]);
  Serial.println(line_sensors[i].misura); }
}

void TestRullo(){
  PhoenixRullo_start();
  PhoenixDrive_setSpeed(&drive, 0,1,0);
  PhoenixDrive_handle(&drive);
}
/**
 * avanti = 0, 1, 0      per toccare la vel_max imposta a 2
 * indietro = 0, -1, 0
 * destra = 1, 0, 0
 * sinistra -1, 0, 0
 * 
 * per IMPOSTARE VELOCITA' ad un motore:
 * PhoenixJoint_handle(&joints[0]);
 * PhoenixJoint_setSpeed(&joints[0], 255);
 * 
 * per Mandare avanti il robot:
 * PhoenixDrive_setSpeed(&drive, 0,2,0);
 * PhoenixDrive_handle(&drive);
 */

void loop() {
  
  Encoder_sample();
  Serial.print(Encoder_getValue(0));
  Serial.print("\t");
  Serial.print(Encoder_getValue(1));
  Serial.print("\t");
  Serial.print(Encoder_getValue(2));
  Serial.println("\t");
}
