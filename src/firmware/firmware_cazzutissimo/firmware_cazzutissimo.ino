
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
#include "ares_management.h"

const uint8_t ENABLE_LINE_CALIB = 0;
static uint8_t ENABLE_SOLENOIDE = 0;
static uint8_t FLAG_ALLINEAMENTO = 0;
static uint8_t ENABLE_STOP = 0;
static uint8_t escape_flag_prec = 0;


/*void TestEncoderFn() {
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
}*/



int led1 = 8;
int led2 = 33;
int led3 = 9;  //alto a destra
int led4 = 12;  //per calibrazione
int led5 = 10;  //NON FUNZICA
int led6 = 35; //basso a sinistra
int led7 = A7;  //centrale
int led8 = 37;  //alto a sinistra
int encoder_sel = 40;
int batteria = A2;
int solenoid = 43;

void setup() {
  //pin
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(batteria, INPUT);
  pinMode(solenoid, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial initialized...");
  //PIXY
  Serial.println("Initializing Camera...");
  delay(1000);
 // PhoenixCamera_init(&_pixy);
  Serial.println("Camera initialized...");
  //ENCODER
  Encoder_init();
  Serial.println("Encoder initialized...");
  //JOINTS
  for(int i=0;i<NUM_JOINTS;++i) {
    PhoenixJoint_init(&joints[i]);
  }
  Serial.println("Joint inizialized...");
  //DRIVE
  PhoenixDrive_init(&drive, joints);
  //IMU
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

  //EEPROM
  Serial.println("Initializing EEPRPOM...");
  PhoenixEeprom_init();
  Serial.println("EEPROM initialized...");
  //SOLENOIDE
  PhoenixSolenoide_init();
  Serial.println("Solenoide inizialized...");
  //SINGLE ADC
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
    Serial.println();
    uint16_t start = millis();
    while(1){
      PhoenixLineHandler_handle(&line_handler);
      if(millis() - start > 10000){
        Serial.println("funzica");
        break; 
      }
    }
    PhoenixDrive_setSpeed(&drive, 0,0,0);
    PhoenixDrive_handle(&drive);
    PhoenixLineHandler_stopCalib(&line_handler);
    PhoenixEeprom_storeLineSensor();

    // QUI 
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
    PhoenixLineHandler_stopCalibBlack(&line_handler);

    //QUI
    */
    for(int i=0;i<6;++i){
      line_sensors[i].soglia_black = 0;
    }
    PhoenixEeprom_storeLineSensor();
    while(1);

  }
  
  Serial.println("Loading line params from eeprom...");
  PhoenixEeprom_loadLineSensor();
  for(int i=0;i<9;i++){
    Serial.print(line_sensors[i].soglia);
    Serial.print(" ");
    Serial.print(line_sensors[i].soglia_black);
    Serial.print(" ");
  }
  Serial.println();
  Timer_init();
  Serial.println("Timers initialized...");

  
  /*struct Timer* t1_fn=Timer_create(1000/50, 
    pixyTimerFn, NULL);
  Timer_start(t1_fn);*/
  
  struct Timer* t2_fn = Timer_create(5, imuTimerFn, NULL);
  Timer_start(t2_fn);

  struct Timer* t3_fn = Timer_create(1000, solenoideTimerFn, NULL);
  Timer_start(t3_fn);

  /*while(digitalRead(encoder_sel) != LOW){
      digitalWrite(led4, HIGH);
    }
    digitalWrite(led4, LOW);*/
}

volatile uint8_t imu_handle_flag=0;
volatile uint8_t pixy_handle_flag=0;

void* imuTimerFn() {
  imu_handle_flag=1;
}

void* pixyTimerFn() {
  pixy_handle_flag=1;
}

void* solenoideTimerFn(){
  ENABLE_SOLENOIDE = 0;
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
  for(int i=0;i<3;i++){
  //Serial.print(PhoenixLineSensor_getStatus(&line_sensors[i]));
  //Serial.print("\t");
  PhoenixLineSensor_handle(&line_sensors[i]);
  //Serial.print(" ");

  Serial.print(line_sensors[i].misura); 
  Serial.print(" ");
  /*Serial.print(line_sensors[i].soglia);
  Serial.print(" ");*/
  /*
  Serial.print(line_sensors[i].soglia_black);
  Serial.print(" ");*/
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

void Test_Encoder(void){
  PhoenixDrive_setSpeed(&drive, 0,1,0);
  PhoenixDrive_handle(&drive);
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
    x=line_handler.escape_x/8;
    y=line_handler.escape_y/8;
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

void Test_EscapeLinePortiere(void){
  double x=0;
  double y=0;
  double t=0;

  PhoenixImu_handle(&imu);
  t=-imu.output_pid/180.0;
  PhoenixLineHandler_handle(&line_handler);
  if(line_handler.escape_flag == 1){
    x=line_handler.escape_x/8;
    y=line_handler.escape_y/8;
  }
  else{
    x=0;
    y=0.5;
    t=-imu.output_pid/180;
  }
  
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
}

void TestStranoPerLine(void){
  PhoenixLineHandler_handle(&line_handler);
  if(line_handler.escape_flag == 1){
    digitalWrite(led3, HIGH);
  }
  else{
    digitalWrite(led3, LOW);
  }
}

void Test_pixy(void){
  static double t=0.0;
  static double x=0.0;
  static double y=0.0;
  static double t_prev=0.0;
    if(PhoenixCamera_getBallStatus(&_pixy)){
      t=-_pixy.output_pid_camera/180;
      Serial.print(t);
      Serial.println();
      t_prev=t;
    } 
    /*
    else{
      t=-imu.output_pid/180;
      x=0;
      y=0;
    }*/
    PhoenixDrive_setSpeed(&drive, x,y,t);
    PhoenixDrive_handle(&drive);
  }

void SolenoideDriver(void){
  PhoenixSolenoide_start();
  delay(100);
  PhoenixSolenoide_stop();
  delay(60);
}

void playFn() {
  double t=0;
  double x=0;
  double y=0;
  double Area = _pixy.area_ball;
  double valore_const = 1.27777;
  PhoenixImu_handle(&imu);
  PhoenixLineHandler_handle(&line_handler);
  if(PhoenixCamera_getBallStatus(&_pixy)){
    ENABLE_STOP = 0;
     x = (-imu.x)*valore_const;
     y = (1-imu.y)*valore_const;
     t = _pixy.output_pid_camera/180;
    if(modulo(x,y) < 0.40){
      x = imu.x;
      y = imu.y;
      t = _pixy.output_pid_camera/180;
      FLAG_ALLINEAMENTO = 1;
    }
    if(Area > 30000 && ENABLE_SOLENOIDE == 0){
      delay(30);
      PhoenixSolenoide_start();
      delay(30);
      PhoenixSolenoide_stop();
      delay(60);
      ENABLE_SOLENOIDE = 1;
    }
    if(Area > 20000 && FLAG_ALLINEAMENTO == 1){
      x = 0;
      y = 1;
      t = -imu.output_pid/180;
    }
  }
  else{
    x = 0;
    y = -0.87777;
    t = -imu.output_pid/180;
    FLAG_ALLINEAMENTO = 0;
  }
  /*
  if(line_handler.escape_flag == 1){
    x = line_handler.escape_x;
    y = line_handler.escape_y;
    t = -imu.output_pid/180;
}*/
   /* if(escape_flag_prec == 0){
       ++ ENABLE_STOP;
       Serial.println("funzica");
    }
  }
  if(ENABLE_STOP == 2){
    x = line_handler.escape_x;
    y = line_handler.escape_y;
    t = -imu.output_pid/180;
    PhoenixDrive_setSpeed(&drive, x,y,t);
    PhoenixDrive_handle(&drive);
    delay(200);
    ++ ENABLE_STOP;
  }
  if(ENABLE_STOP == 3){
    x = 0;
    y = 0;
    t = -imu.output_pid/180;
  }
  escape_flag_prec = line_handler.escape_flag;*/
  PhoenixDrive_setSpeed(&drive, x, y, t);
  PhoenixDrive_handle(&drive);
}


void portierefn(void){
  static double t=0;
  static double x=0;
  static double y=0;
  static double t_prev=0;
  PhoenixImu_handle(&imu);
  PhoenixLineHandler_handle(&line_handler);

  if(PhoenixCamera_getBallStatus(&_pixy)){
    t = -_pixy.output_pid_camera/180;
    if(imu.x > 0){
      x = -imu.y*2;
      y = imu.x*2;
    }
    else{
      x = imu.y*2;
      y = -imu.x*2;
    }
    if(modulo(imu.x,imu.x) < 0.3){
      x = 0;
      y = 0.4;
    }
  }
  else{
    x = 0;
    y = 0;
    t = -imu.output_pid/180;
  }
  if(line_handler.escape_flag == 1){
    x= line_handler.escape_x/12;
    y= line_handler.escape_y/12;
    t= -imu.output_pid/180;
  }
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

void OnLight(void){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  analogWrite(led7, 255);
  digitalWrite(led8, HIGH);
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
  /*if(pixy_handle_flag) {
    PhoenixCamera_handle(&_pixy);
    pixy_handle_flag=0;
  }*/

//Joint funzica singolo but no in all joint e devo da capi il perchè 
 /* for(int i=0;i<NUM_JOINTS;++i){
  PhoenixJoint_setSpeed(&joints[i], 255);
  PhoenixJoint_handle(&joints[i]);
  }*/
//Drive 
  /*PhoenixDrive_setSpeed(&drive, 0,1,0);
  PhoenixDrive_handle(&drive);*/
} 
