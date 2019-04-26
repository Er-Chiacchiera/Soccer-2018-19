

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
    PhoenixImu_handle(g->imu);
    PhoenixLineHandler_handle(g->line_handler);
    if(PhoenixCamera_getBallStatus(g->_pixy)){
        g->x = (-g->imu->x)*g->value_const;
        g->y = (1-g->imu->y)*g->value_const;
        g->t = g->_pixy->output_pid_camera/180;
        if(modulo(g->x,g->y) < g->value_modulo){
            g->x = g->imu->x;
            g->y = g->imu->y;
            g->t = g->_pixy->output_pid_camera/180;
        }
        if(g->line_handler->escape_flag == 1){
            g->x = 0;
            g->y = 0;
            g->t = -g->imu->output_pid/180;
        }
    }
    else{
        g->x = 0;
        g->y = -0.87777;
        g->t = -g->imu->output_pid/180;
    }
    if(g->line_handler->escape_flag == 1){
        g->x = g->line_handler->escape_x;
        g->y = g->line_handler->escape_y;
        g->t = -g->imu->output_pid/180;
    }
    PhoenixDrive_setSpeed(g->drive, g->x,g->y,g->t);
    PhoenixDrive_handle(g->drive);
}

void PhoenixManagement_handlePortiere(PhoenixManagement * g){
    PhoenixImu_handle(g->imu);
    PhoenixLineHandler_handle(g->line_handler);
    if(PhoenixCamera_getBallStatus(g->_pixy)){
        g->t = -g->_pixy->output_pid_camera/180;
        if(g->imu->x > 0){
            g->x = -g->imu->y;
            g->y = g->imu->x;
            g->t = -g->_pixy->output_pid_camera/180;
        }
        else{
            g->x = g->imu->y;
            g->y = -g->imu->x;
            g->t = -g->_pixy->output_pid_camera/180;
        }
    }
    else{
        g->x = 0;
        g->y = 0;
        g->t = -g->imu->output_pid/180;
    }
    if(g->line_handler->escape_flag == 1){
        g->x = g->line_handler->escape_x;
        g->y = g->line_handler->escape_y;
        g->t = -g->imu->output_pid/180;
    }
    PhoenixDrive_setSpeed(g->drive, g->x,g->y,g->t);
    PhoenixDrive_handle(g->drive);
}


void PhoenixManagement_reset(PhoenixManagement * g){
    g->x = 0;
    g->y = 0;
    g->t = 0;
    g->t_prev = 0;
}