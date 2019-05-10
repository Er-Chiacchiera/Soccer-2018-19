

#include "ares_ManagementUltrasound.h"

void PhoenixManagementUltra_init(ManagementUltrasound * m){
    m->flag_wall = 0;
}

void PhoenixManagementUltra_handle(ManagementUltrasound * m){
    for(int i=0;i<4;i++){
        Ultrasound_handle(&sound);
        if(PhoenixUltrasound_getWallStatus(&sound) == 1){
            m->flag_wall = 1;
        }
        else{
            m->flag_wall = 0;
        }
    }
    for(int i=0;i<4;++i){
        PhoenixUltrasound_returnDistance(&sound);
    }
}

void PhoenixManagementUltra_reset(ManagementUltrasound * m){
    m->flag_wall = 0;
}

int PhoenixManagementUltra_returnFlag(ManagementUltrasound * m){
    return m->flag_wall;
}