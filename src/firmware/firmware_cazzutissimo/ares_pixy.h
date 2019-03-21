/**
 * phoenix_pixy.h
 **/

#pragma once

#include <Pixy2.h>

#define BALL_SIG 1
#define BALL_RELIABLE_AGE 100

typedef struct {
  int8_t ball_detection;
  uint16_t ball_x;
  uint16_t ball_y;
  uint16_t ball_w;
  uint16_t ball_h;
  uint8_t ball_age;
}PhoenixCamera;



void PhoenixCamera_init(PhoenixCamera* p);


void PhoenixCamera_handle(PhoenixCamera* p);


uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallX(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallY(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallW(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallH(PhoenixCamera* p);

uint8_t PhoenixCamera_getBallAge(PhoenixCamera * p);


uint16_t PhoenixCamera_getBlocks(PhoenixCamera* p);


