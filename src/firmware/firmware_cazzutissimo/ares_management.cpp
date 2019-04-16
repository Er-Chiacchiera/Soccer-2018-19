

#include  "ares_management.h"


void PhoenixManagement_init(PhoenixManagement * g){
    g->x = 0;
    g->y = 0;
    g->t = 0;
    g->t_prev = 0;
    g->value_const = 0;
    g->value_modulo = 0;
}

void PhoenixManagement_handleAttack(PhoenixManagement * g){
    PhoenixImu_handle(&imu);
    PhoenixLineHandler_handle(&line_handler);
    if(PhoenixCamera_getBallStatus(&_pixy)){
        g->x = (-imu.x)*g->value_const;
        g->y = (1-imu.y)*g->value_const;
        g->t = _pixy.output_pid_camera/180;
        if(modulo(g->x,g->y) < g->value_modulo){
            g->x = imu.x;
            g->y = imu.y;
            g->t = _pixy.output_pid_camera/180;
        }
        if(line_handler.escape_flag == 1){
            g->x = 0;
            g->y = 0;
            g->t = -imu.output_pid/180;
        }
    }
    else{
        g->x = 0;
        g->y = -0.87777;
        g->t = -imu.output_pid/180;
    }
    if(line_handler.escape_flag == 1){
        g->x = line_handler.escape_x;
        g->y = line_handler.escape_y;
        g->t = -imu.output_pid/180;
    }
    PhoenixDrive_setSpeed(&drive, g->x,g->y,g->t);
    PhoenixDrive_handle(&drive);
}

void PhoenixManagement_handlePortiere(PhoenixManagement * g){
    PhoenixImu_handle(&imu);
    PhoenixLineHandler_handle(&line_handler);
    if(PhoenixCamera_getBallStatus(&_pixy)){
        g->t = -_pixy.output_pid_camera/180;
        if(imu.x > 0){
            g->x = -imu.y;
            g->y = imu.x;
            g->t = -_pixy.output_pid_camera/180;
        }
        else{
            g->x = imu.y;
            g->y = -imu.x;
            g->t = -_pixy.output_pid_camera/180;
        }
    }
    else{
        g->x = 0;
        g->y = 0;
        g->t = -imu.output_pid/180;
    }
    if(line_handler.escape_flag == 1){
        g->x = line_handler.escape_x;
        g->y = line_handler.escape_y;
        g->t = -imu.output_pid/180;
    }
    PhoenixDrive_setSpeed(&drive, g->x,g->y,g->t);
    PhoenixDrive_handle(&drive);
}


void PhoenixManagement_reset(PhoenixManagement * g){
    g->x = 0;
    g->y = 0;
    g->t = 0;
    g->t_prev = 0;
}