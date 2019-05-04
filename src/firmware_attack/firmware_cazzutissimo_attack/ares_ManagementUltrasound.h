/**
 * ares_ManagementUltrasound.h
 */

#pragma once
#include <Arduino.h>
#include "ares_ultrasuono.h"


typedef struct{
    Ultrasound * sound;
    int flag_wall;
} ManagementUltrasound;

void PhoenixManagementUltra_init(ManagementUltrasound * m);
void PhoenixManagementUltra_handle(ManagementUltrasound * m);
void PhoenixManagementUltra_reset(ManagementUltrasound * m);
int PhoenixManagementUltra_returnFlag(ManagementUltrasound * m);
int PhoenixManagementUltra_returnDistance(ManagementUltrasound * m);