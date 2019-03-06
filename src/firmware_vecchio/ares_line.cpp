#include "ares_line.h"
#include "ares_Line_internal.h"    //includo delle librerie
#include <math.h>

static void AresLineHandler_updateEDir(AresLineHandler* h){ //creo una funzione che aggiorna 
    h->escape_direction[0] = -h->border_x;                  //le direzioni a linea rilevata
    h->escape_direction[1] = -h->border_y;
    h->escape_direction[2] = 0;
}

void AresLineHandler_init(AresLineHandler* h, LineDetector* ld){  //creo una funzione che inizializza
    h->ld=ld;                                                    //e imposta il valore di ogni direzione
    h->escape_flag = 0;                                         // uguale a 0
    for(int i=0; i<3; i++)
        h->escape_direction[i] = 0;
}

int AresLineHandler_handle(AresLineHandler* h){
    h->border_x = 0;
    h->border_y = 0;
    //interrogo tutti i sensori e aggiorno il loro stato 
    for(i=0;i<NUM_LINEDETECTORS;i++)
    {
        if(LineDetector_handle(&h->ld[i])<0)
        {
            return -1;
        }
    }
    for(int i=0;i<NUM_LINEDETECTORS;i++)
    {
        if((h->mask>>i & 0x01) == 0) 
        {
            if(h->ld[i].detected)
            {
                h->mask |= 0x1<<i;
                h->border_x+=h->ld[i].x;
                h->border_y+=h->ld[i].y;
                AresLineHandler_updateEDir(h);
            }
        }
    }
    return 0;
}

void AresLineHandler_reset(AresLineHandler* h)
{
    h->escape_flag=0;
    h->mask=0;
    for(int i=0;i<3;i++)
    {
        h->escape_direction[i]=0;
    }
    for(int i=0;i<NUM_LINEDETECTORS;i++)
    {
        AresLineHandler_reset(&h->ld[i]);
    }
}