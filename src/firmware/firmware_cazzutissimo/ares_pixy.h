/**
 * phoenix_pixy.h
 **/

#pragma once

#include <Pixy.h>

#define BALL_SIG 1
#define BALL_RELIABLE_CTR 5

typedef struct {
  int8_t ball_detection;
  uint16_t ball_x;
  uint16_t ball_y;
  uint16_t ball_w;
  uint16_t ball_h;
  uint16_t ball_age;
}PhoenixCamera;



void PhoenixCamera_init(PhoenixCamera* p);


void PhoenixCamera_handle(PhoenixCamera* p);


uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallX(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallY(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallW(PhoenixCamera* p);


uint16_t PhoenixCamera_getBallH(PhoenixCamera* p);


uint16_t PhoenixCamera_getBlocks(PhoenixCamera* p);


