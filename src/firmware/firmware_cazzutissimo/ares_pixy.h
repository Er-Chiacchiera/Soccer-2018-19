/**
 * phoenix_pixy.h
 **/

#pragma once
#include <Arduino.h>

#define BALL_SIG 1
#define DOOR_SIG 2
#define BALL_RELIABLE_AGE 80
#define DOOR_RELIABLE_AGE 600

typedef struct {
  int8_t ball_detection;
  int8_t door_detection;
  uint16_t ball_x;
  uint16_t ball_y;
  uint16_t ball_w;
  uint16_t ball_h;
  uint16_t door_x;
  uint16_t door_y;
  uint16_t door_w;
  uint16_t door_h;
  uint8_t ball_age;
  uint8_t door_age;
  int area_ball;
  int area_door;
}PhoenixCamera;



void PhoenixCamera_init(PhoenixCamera* p);


void PhoenixCamera_handle(PhoenixCamera* p);


uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p);


uint8_t PhoenixCamera_getDoorStatus(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallX(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallY(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallW(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallH(PhoenixCamera* p);


uint8_t PhoenixCamera_getBallAge(PhoenixCamera * p);


uint8_t PhoenixCamera_getDoorAge(PhoenixCamera * p);


uint16_t PhoenixCamera_getBlocks(PhoenixCamera* p);


