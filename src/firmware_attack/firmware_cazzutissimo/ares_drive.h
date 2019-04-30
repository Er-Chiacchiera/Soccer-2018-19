/**
 * phoenix_drive.h
 **/
#pragma once
#include "ares_params.h"
#include "ares_joints.h"

typedef struct {
  PhoenixJoint* joints;

  double vel_x_desiderata;
  double vel_y_desiderata;
  double rot_desiderata;

} PhoenixDrive;


void PhoenixDrive_init(PhoenixDrive* d, PhoenixJoint* joint_array);
void PhoenixDrive_setSpeed(PhoenixDrive* d, double x, double y, double r);
void PhoenixDrive_handle(PhoenixDrive* d);
void PhoenixDrive_reset(PhoenixDrive* d);
