#pragma once

//Converte gli gradi in radianti 
#define degreesToRadians(angleDegrees) (angleDegress * M_PI / 180.0)  //macro 

//converte i radianti in angoli
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

#define NUM_MOTORS 3
#define NUM_LINEADC 4  //NUMERI DEL MODULO ADS1015
#define NUM_LINEDETECTORS 8 //NUMERO TOTALE DI LINEE VISTE