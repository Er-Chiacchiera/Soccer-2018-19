/**
 * bno055.cpp
 **/

#include "bno055.h"

static uint8_t received_buf[8];
#define RECV_BUF_SIZE 8

/**
 * Asks for the value saved in reg
 **/
static uint8_t read8(uint8_t addr, BNO055_reg reg) {
  uint8_t data=0x00;

  // Transmission of request
  Wire.beginTransmission(addr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();
  // Receive the data
  Wire.requestFrom(addr,(uint8_t)1);
  data=Wire.read();
  return data;  
}

static uint16_t read16(uint8_t addr, BNO055_reg reg) {
  uint16_t msb=0;
  uint16_t lsb=0;

  // Transmission of request
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  // Receive the data
  Wire.requestFrom(addr, sizeof(uint16_t));
  lsb=Wire.read();
  msb=Wire.read();
  return (lsb | msb<<8);
}

static BNO055_result readLen(uint8_t addr, BNO055_reg reg, uint8_t* buf, uint8_t len) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, len);

  for(int i=0;i<len;++i) {
    buf[i]=Wire.read();
  }
  return SUCCESS;
}

static void write8(uint8_t addr, BNO055_reg reg, uint8_t data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

static void _BNO055_setMode(uint8_t addr, BNO055_op op) {
  write8(addr, OPR_MODE, op);
  delay(MODE_SWITCH_DELAY);
}

/**
 * Initializes I2C channel in clock stretching mode
 * then asks the dev for his ID saved in the CHIP_ID Register.
 * Fix everything on registers and stuff
 * finally enable the selected operating mode
 **/
// BNO055_result
uint8_t BNO055_init(BNO055* b) {
  uint8_t temp=0x00;
  // Initializes I2C (through Wire library)
  // im lazy :/
  Wire.begin();

  uint8_t id=0;  
  id=read8(b->i2c_addr, CHIP_ID);
  if(id!=BNO055_CHIP_ID) {
    // wait for boot
    delay(1000);
    id=read8(b->i2c_addr, CHIP_ID);
    if(id!=BNO055_CHIP_ID)
      return UNKNOWN_DEVICE;
  }
   

  // At this point connection between MCU and DEV is complete
  // time to initialize everything!
  
  // set units and output format
  temp |=
    (b->unit_acc<<ACCEL_UNIT) |    
    (b->unit_angr<<ANGULAR_RATE_UNIT) |
    (b->unit_eul<<EULER_ANGLES_UNIT) |
    (b->unit_temp<<TEMPERATURE_UNIT) |
    (b->invert_heading<<FUSION_DATA_OUTPUT_FORMAT);
  write8(b->i2c_addr, UNIT_SEL, temp);
  temp=0;

  // TODO
  

  // set requested operation mode
  _BNO055_setMode(b->i2c_addr, b->op);
  return SUCCESS;
}


static void _BNO055_getHeading(BNO055* b, uint8_t* buf) {
  readLen(b->i2c_addr, EUL_HEADING_LSB, buf, 6);

  int16_t d1 = ((int16_t)(buf[0]) | (int16_t)(buf[1])<<8);
  int16_t d2 = ((int16_t)(buf[2]) | (int16_t)(buf[3])<<8);
  int16_t d3 = ((int16_t)(buf[4]) | (int16_t)(buf[5])<<8);

  double div_factor=UNIT_DEG_RATIO;
  if(b->unit_eul == RAD) {
    div_factor=UNIT_RAD_RATIO;
  }
  
  b->eul_heading=((double)d1)/div_factor;
  b->eul_roll=((double)d2)/div_factor;
  b->eul_pitch=((double)d3)/div_factor;
}

/**
 * Depending on the op selected, executes and 
 * gets data from the Device
 **/
void BNO055_handle(BNO055* b) {
  _BNO055_getHeading(b, received_buf);  
  return;
}
