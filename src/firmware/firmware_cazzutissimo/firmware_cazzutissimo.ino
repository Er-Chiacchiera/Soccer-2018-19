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
#include "utils.h"

const uint8_t ENABLE_LINE_CALIB = 0;



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

int led1 = 8;
int led2 = 33;
int led3 = 9;
int led4 = 12;
int led5 = 10;
int led6 = 35;
int led7 = A7;
int led8 = 37;
int encoder_sel = 40;
int batteria = A2;
int solenoide = 43;

void setup() {
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(batteria, INPUT);
  pinMode(solenoide, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial initialized...");

  Serial.println("Initializing Camera...");
  delay(1000);
  PhoenixCamera_init(&_pixy);
  Serial.println("Camera initialized...");

  for(int i=0;i<NUM_JOINTS;++i) {
    PhoenixJoint_init(&joints[i]);
  }
  Serial.println("Joint inizialized...");

  PhoenixDrive_init(&drive, joints);

  
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
  PhoenixImu_setOffset(&imu, imu.heading_attuale);

  Encoder_init();
  
  Serial.println("Initializing EEPRPOM...");
  PhoenixEeprom_init();
  Serial.println("EEPROM initialized...");
  
  PhoenixRullo_init();
  Serial.println("Rullo inizialized...");

  PhoenixLineSensor_ADCBegin();
  for(int i=0;i<NUM_LINE_SENSORS;++i) {
    PhoenixLineSensor_init(&line_sensors[i]);
  }
  Serial.println("Line Sensors initialized...");
  PhoenixLineHandler_init(&line_handler, line_sensors);
  Serial.println("Line Handler initialized...");
  pinMode(encoder_sel, INPUT_PULLUP);
  digitalWrite(led4, LOW);
  if(ENABLE_LINE_CALIB == 1) {
    while(digitalRead(encoder_sel) != LOW){
      digitalWrite(led4, HIGH);
    }
    digitalWrite(led4, LOW);
    PhoenixLineHandler_startCalib(&line_handler);
    PhoenixDrive_setSpeed(&drive, 0,0,1);
    PhoenixDrive_handle(&drive);
    uint16_t start = millis();
    while(1){
      PhoenixLineHandler_handle(&line_handler);
            Serial.print(start);
            Serial.print(" ");
            Serial.println(millis());
      if(millis() - start > 5000){
        Serial.println("funzica");
        break; 
      }
    }
    PhoenixDrive_setSpeed(&drive, 0,0,0);
    PhoenixDrive_handle(&drive);
    PhoenixLineHandler_stopCalib(&line_handler);
    PhoenixEeprom_storeLineSensor();
    /*
    while(digitalRead(encoder_sel) != LOW){
      digitalWrite(led4, HIGH);
    }
    digitalWrite(led4, LOW);
    PhoenixLineHandler_startCalibBlack(&line_handler);
    PhoenixDrive_setSpeed(&drive, 0,0,1);
    PhoenixDrive_handle(&drive);
    start = millis();
    while(1){
      PhoenixLineHandler_handle(&line_handler);
      if(millis() - start > 5000){
        break; 
      }
    }
    PhoenixDrive_setSpeed(&drive, 0,0,0);
    PhoenixDrive_handle(&drive);
    PhoenixLineHandler_stopCalibBlack(&line_handler);*/
    for(int i=0;i<NUM_LINE_SENSORS;++i){
      line_sensors[i].soglia_black = 0;
    }
    PhoenixEeprom_storeLineSensor();
    while(1);

  }
     

  Serial.println("Loading line params from eeprom...");
  PhoenixEeprom_loadLineSensor();
  Timer_init();
  Serial.println("Timers initialized...");

  
  struct Timer* t1_fn=Timer_create(1000/50, 
    pixyTimerFn, NULL);
  Timer_start(t1_fn);
  
  struct Timer* t2_fn = Timer_create(5, imuTimerFn, NULL);
  Timer_start(t2_fn);
  
  
  
}

volatile uint8_t imu_handle_flag=0;
volatile uint8_t pixy_handle_flag=0;

void* imuTimerFn() {
  imu_handle_flag=1;
}

void* pixyTimerFn() {
  pixy_handle_flag=1;
}

void Test_connections(void){
  PhoenixJoint_setSpeed(&joints[0], 150); 
  Serial.println(joints[0].velocita);
  PhoenixJoint_handle(&joints[0]);
  PhoenixJoint_setSpeed(&joints[1], 150); 
  PhoenixJoint_handle(&joints[1]);
  PhoenixJoint_setSpeed(&joints[2], 150); 
  PhoenixJoint_handle(&joints[2]);
}
  
void Test_ImuPid(void){
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

void Test_LineInternal(void){
  for(int i=0;i<9;i++){
  //Serial.print(PhoenixLineSensor_getStatus(&line_sensors[i]));
  //Serial.print("    ");
  PhoenixLineSensor_handle(&line_sensors[i]);
  //Serial.print(" ");

  Serial.print(line_sensors[i].misura); 
  Serial.print(" ");
  /**
  Serial.print(line_sensors[i].soglia);
  Serial.print(" ");
  Serial.print(line_sensors[i].soglia_black);
  Serial.print(" ");**/
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
  PhoenixDrive_setSpeed(&drive, 0,1,-imu.output_pid/180);
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
    t=-imu.output_pid/180;
  }
  
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
  Serial.println(PhoenixLineHandler_getStatus(&line_handler));
}

void Test_pixy(void){
  double t=0.0;
  double x=0.0;
  double y=0.0;
  static double t_prev=0.0;
    if(PhoenixCamera_getBallStatus(&_pixy)){
      t=_pixy.output_pid_camera/180;
      Serial.print(t);
      Serial.println();
      t_prev=t;
      x=-imu.x;
      y=1-imu.y;
    } else {
      t=-imu.output_pid/180;
      x=0;
      y=0;
    }
    PhoenixDrive_setSpeed(&drive, x,y,t);
    PhoenixDrive_handle(&drive);
  }

void playFn() {
  double t=0;
  double x=0;
  double y=0;
  double Area = _pixy.area_ball;
  PhoenixImu_handle(&imu);
  PhoenixLineHandler_handle(&line_handler);
  if(PhoenixCamera_getBallStatus(&_pixy)){
     x = (-imu.x)*1.2;
     y = (1-imu.y)*1.2;
     t = _pixy.output_pid_camera/180;
    if(modulo(x,y) < 0.35){
      x = imu.x;
      y = imu.y;
      t = _pixy.output_pid_camera/180;
    }
    if(abs(Area) > 10000 && _pixy.ball_y < 90){
      delay(130);
      digitalWrite(solenoide, HIGH);
      delay(25);
      digitalWrite(solenoide, LOW);
      delay(100);
    }
  }
  else{
    x = 0;
    y = -0.7;
    t = -imu.output_pid/180;
  }
  if(line_handler.escape_flag == 1){
    x = line_handler.escape_x;
    y = line_handler.escape_y;
    t = -imu.output_pid/180;
  }
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
  Serial.println(line_handler.escape_flag);
}


void portierefn(void){
  double t=0;
  double x=0;
  double y=0;
  static double t_prev=0;
  PhoenixImu_handle(&imu);
  PhoenixLineHandler_handle(&line_handler);

  if(PhoenixCamera_getBallStatus(&_pixy)){
    t = _pixy.output_pid_camera/180;
    if(imu.x > 0){
      x = -imu.y;
      y = imu.x;
      t = _pixy.output_pid_camera/180;
    }
    else{
      x = imu.y;
      y = -imu.x;
      t = _pixy.output_pid_camera/180;
    }
  }
  else{
    x = 0;
    y = 0;
    t = -imu.output_pid/180;
  }
  /*
  if(line_handler.escape_flag == 1){
    x= line_handler.escape_x;
    y= line_handler.escape_y;
    t= -imu.output_pid/180;
  }*/
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
}

void Test_pixyBall(void){
  double x;
  double y;
  double t;
  PhoenixImu_handle(&imu);
  if(PhoenixCamera_getBallStatus(&_pixy)){
    x = -imu.x;
    y = 1-imu.y;
    t = _pixy.output_pid_camera/180;
  }
  else{
    x = 0;
    y = 0;
    t = -imu.output_pid/180;
  }
  PhoenixDrive_setSpeed(&drive, x,y,t);
  PhoenixDrive_handle(&drive);
}

void batteria_bassa(void){
  if(analogRead(batteria) < 724){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    analogWrite(led7, 255);
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    analogWrite(led7, 0);
  }
}

/**
 * avanti = 0, 1, 0      per toccare la vel_max imposta a 2
 * indietro = 0, -1, 0
 * destra = 1, 0, 0
 * sinistra -1, 0, 0
 */

void loop() {
  if(imu_handle_flag) {
    PhoenixImu_handle(&imu);
    imu_handle_flag=0;
  }
  if(pixy_handle_flag) {
    PhoenixCamera_handle(&_pixy);
    pixy_handle_flag=0;
  }
  playFn();
}
