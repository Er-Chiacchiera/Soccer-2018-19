/**
 * bno055.h
 * Built by Emanuele Giacomini
 * for Robocup Jr. robots
 **/

#pragma once
#include <Arduino.h>
#include <Wire.h>

typedef enum {
  CHIP_ID=0x00,
  ACC_ID=0x01,
  MAG_ID=0x02,
  GYR_ID=0x03,
  SW_REV_ID_LSB=0x04,
  SW_REV_ID_MSB=0x05,
  BL_REV_ID=0x06,//Bootloader Version
  PAGE_ID=0x07,
  // accelerometer data 
  ACC_DATA_X_LSB=0x08,
  ACC_DATA_X_MSB=0x09,
  ACC_DATA_Y_LSB=0x0A,
  ACC_DATA_Y_MSB=0x0B,
  ACC_DATA_Z_LSB=0x0C,
  ACC_DATA_Z_MSB=0x0D,
  // magnetometer data
  MAG_DATA_X_LSB=0x0E,
  MAG_DATA_X_MSB=0x0F,
  MAG_DATA_Y_LSB=0x10,
  MAG_DATA_Y_MSB=0x11,
  MAG_DATA_Z_LSB=0x12,
  MAG_DATA_Z_MSB=0x13,
  // gyroscope data
  GYR_DATA_X_LSB=0x14,
  GYR_DATA_X_MSB=0x15,
  GYR_DATA_Y_LSB=0x16,
  GYR_DATA_Y_MSB=0x17,
  GYR_DATA_Z_LSB=0x18,
  GYR_DATA_Z_MSB=0x19,
  // heading data
  EUL_HEADING_LSB=0x1A,
  EUL_HEADING_MSB=0x1B,
  // roll data
  EUL_ROLL_LSB=0x1C,
  EUL_ROLL_MSB=0x1D,
  // pitch data
  EUL_PITCH_LSB=0x1E,
  EUL_PITCH_MSB=0x1F,
  // quaternion Data
  QUA_DATA_W_LSB=0x20,
  QUA_DATA_W_MSB=0x21,
  QUA_DATA_X_LSB=0x22,
  QUA_DATA_X_MSB=0x23,
  QUA_DATA_Y_LSB=0x24,
  QUA_DATA_Y_MSB=0x25,
  QUA_DATA_Z_LSB=0x26,
  QUA_DATA_Z_MSB=0x27,
  // linear acceleration Data
  LIA_DATA_X_LSB=0x28,
  LIA_DATA_X_MSB=0x29,
  LIA_DATA_Y_LSB=0x2A,
  LIA_DATA_Y_MSB=0x2B,
  LIA_DATA_Z_LSB=0x2C,
  LIA_DATA_Z_MSB=0x2D,
  // gravity vector Data
  GRV_DATA_X_LSB=0x2E,
  GRV_DATA_X_MSB=0x2F,
  GRV_DATA_Y_LSB=0x30,
  GRV_DATA_Y_MSB=0x31,
  GRV_DATA_Z_LSB=0x32,
  GRV_DATA_Z_MSB=0x33,
  TEMP=0x34,
  CALIB_STAT=0x35,
  ST_RESULT=0x36,
  INT_STA=0x37,
  SYS_CLK_STATUS=0x38,
  SYS_STATUS=0x39,// System Status Code
  SYS_ERR=0x3A, // System Error Code
  UNIT_SEL=0x3B,
  OPR_MODE=0x3D,
  PWR_MODE=0x3E,
  SYS_TRIGGER=0x3F, 
  TEMP_SOURCE=0x40,
  AXIS_MAP_CONFIG=0x41,
  AXIS_MAP_SIGN=0x42,
  // Accelerometer offset
  ACC_OFFSET_X_LSB=0x55,
  ACC_OFFSET_X_MSB=0x56,
  ACC_OFFSET_Y_LSB=0x57,
  ACC_OFFSET_Y_MSB=0x58,
  ACC_OFFSET_Z_LSB=0x59,
  ACC_OFFSET_Z_MSB=0x5A,
  // Magnetometer offset
  MAG_OFFSET_X_LSB=0x5B,
  MAG_OFFSET_X_MSB=0x5C,
  MAG_OFFSET_Y_LSB=0x5D,
  MAG_OFFSET_Y_MSB=0x5E,
  MAG_OFFSET_Z_LSB=0x5F,
  MAG_OFFSET_Z_MSB=0x60,
  // Gyroscope offset
  GYR_OFFSET_X_LSB=0x61,
  GYR_OFFSET_X_MSB=0x62,
  GYR_OFFSET_Y_LSB=0x63,
  GYR_OFFSET_Y_MSB=0x64,
  GYR_OFFSET_Z_LSB=0x65,
  GYR_OFFSET_Z_MSB=0x66,
  // Accelerometer radius
  ACC_RADIUS_LSB=0x67,
  ACC_RADIUS_MSB=0x68,
  // Magnetometer radius
  MAG_RADIUS_LSB=0x69,
  MAG_RADIUS_MSB=0x6A
}BNO055_reg;

typedef enum {
CONFIGMODE=0x00,
ACCONLY=0x01,
MAGONLY=0x02,
GYROONLY=0x03,
ACCMAG=0x04,
ACCGYRO=0x05,
MAGGYRO=0x06,
AMG=0x07,
IMU=0x08,
COMPASS=0x09,
M4G=0x0A,
NDOF_FMC_OFF=0x0B,
NDOF=0x0C
}BNO055_op;


typedef enum {
  MS2=0x00,
  MG=0x01,
  DPS=0x00,
  RPS=0x01,
  DEG=0x00,
  RAD=0x01,
  C=0x00,
  F=0x01
}BNO055_unit;

// Units Register's offset
#define ACCEL_UNIT 0
#define ANGULAR_RATE_UNIT 1
#define EULER_ANGLES_UNIT 2
#define TEMPERATURE_UNIT 3
#define FUSION_DATA_OUTPUT_FORMAT 7


// Euler angle data representation
#define UNIT_DEG_RATIO 16
#define UNIT_RAD_RATIO 900

// Operating mode switching times
#define CONFIGMODE_SWITCH_MS 7
#define ANYMODE_SWITCH_MS 19
#define MODE_SWITCH_DELAY 25

/**
 * The I²C interface of the BNO055 is compatible with the 
 * I²C Specification UM10204 Rev. 03 
 * (19 June 2007), available at http://www.nxp.com
 * . The  BNO055  supports  I²C  standard  mode 
 * and fast mode, only 7 - bit address mode is supported.
 * The BNO055 I²C interface uses clock stretching. 
 **/

#define BNO055_I2C_ADDR 0x28
#define BNO055_I2C_ADDR_ALT 0x29
#define BNO055_CHIP_ID 0xA0

typedef enum {
  SUCCESS=0x00,
  UNKNOWN_DEVICE=-0x01
}BNO055_result;

typedef struct {
  uint16_t timestamp;
  // i2c address (default is 0x27)
  uint8_t i2c_addr;
  // operating mode (compass is used on robots for general usage)
  BNO055_op op;
  BNO055_unit unit_acc : 1;
  BNO055_unit unit_angr : 1;
  BNO055_unit unit_eul : 1;
  BNO055_unit unit_temp : 1;
  // Invertex axes
  uint8_t invert_heading : 1;
  // euler 
  double eul_heading;
  double eul_roll;
  double eul_pitch;
  // LIA (LInear Acceleration)
  int16_t lia_x;
  int16_t lia_y;
  int16_t lia_z;
}BNO055;

/**
 * Initializes I2C channel in clock stretching mode
 * then asks the dev for his ID saved in the CHIP_ID Register.
 * Fix everything on registers and stuff
 * finally enable the selected operating mode
 **/
// BNO055_result
uint8_t BNO055_init(BNO055* b);

/**
 * Depending on the op selected, executes and 
 * gets data from the Device
 **/
void BNO055_handle(BNO055* b);
