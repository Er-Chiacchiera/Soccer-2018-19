/**
 * ares_management.h
**/

#pragma once
#include "ares_pixy.h"
#include "ares_line.h"
#include "ares_drive.h"
#include "ares_imu.h"
#include "utils.h"

typedef struct {
    PhoenixImu *imu;
    PhoenixLineHandler *line_handler;
    PhoenixDrive *drive;
    PhoenixCamera *_pixy;
    double x;
    double y;
    double t;
    double t_prev;
    double value_const;
    int value_modulo;
} PhoenixManagement;

void PhoenixManagement_init(PhoenixManagement * g);
void PhoenixManagement_handleAttack(PhoenixManagement * g);
void PhoenixManagement_handlePortiere(PhoenixManagement * g);
void PhoenixManagement_reset(PhoenixManagement * g);