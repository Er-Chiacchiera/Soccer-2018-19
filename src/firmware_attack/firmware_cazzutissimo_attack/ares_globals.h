/**
 * phoenix_globals.h
 **/

#pragma once

#include <Arduino.h>
#include "ares_joints.h"
#include "ares_drive.h"
#include "ares_line.h"
#include "ares_line_internal.h"
#include "bno055.h"
#include "ares_imu.h"
#include "ares_rullo.h"
#include "ares_pixy.h"
#include "Adafruit_ADS1015.h"
#include "ares_management.h"
#include "ares_ultrasuono.h"
#include "ares_ManagementUltrasound.h"

extern PhoenixJoint joints[NUM_JOINTS];
extern PhoenixDrive drive;
extern PhoenixLineSensor line_sensors[];
extern PhoenixLineHandler line_handler;
extern BNO055 dev_bno055;
extern PhoenixImu imu;
extern Adafruit_ADS1015 line_adc;
extern PhoenixCamera _pixy;
extern PhoenixManagement gestione;
extern Ultrasound ultrasuono [NUM_ULTRASOUND];
extern ManagementUltrasound _gestione2;
