/**
 * ares_management
**/

#pragma once
#include "ares_pixy.h"
#include "ares_line.h"
#include "ares_drive.h"
#include "utils.h"
#include "ares_globals.h"

typedef struct {
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