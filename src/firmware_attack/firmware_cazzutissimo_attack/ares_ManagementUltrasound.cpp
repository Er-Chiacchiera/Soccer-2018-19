

#include "ares_ManagementUltrasound.h"

void PhoenixManagementUltra_init(ManagementUltrasound * m){
    m->flag_wall = 0;
}

void PhoenixManagementUltra_handle(ManagementUltrasound * m){
    for(int i=0;i<NUM_ULTRASOUND;i++){
        PhoenixUltrasound_handle(m->sound);
        if(PhoenixUltrasound_getWallStatus(m->sound) == 1){
            m->flag_wall = 1;
        }
        else{
            m->flag_wall = 0;
        }
    }
}

void PhoenixManagementUltra_reset(ManagementUltrasound * m){
    m->flag_wall = 0;
}

int PhoenixManagementUltra_returnFlag(ManagementUltrasound * m){
    return m->flag_wall;
}

int PhoenixManagementUltra_returnDistance(ManagementUltrasound * m){
    for(int i=0;i<NUM_ULTRASOUND;++i){
        PhoenixUltrasound_returnDistance(&sound[i]);
    }
}