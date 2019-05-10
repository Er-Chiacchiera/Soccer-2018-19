#include "ares_drive.h"        //includo la libreria 

static double ares_matrix [NUM_MOTORS] [NUM_MOTORS] =   //creo una variabile di tipo "static" e gli vado a 
{                                                       //passare i valori ottenuti dalla matrice calcolata
    {0.33, -0.33, 0.57},                                
    {0.33, -0.33, -0.57},                               
    {0.33, 0.66, 0}                                     
};

Ares_drive::Ares_drive() {}   

void Ares_drive::init(Joint* joints, JointDati* dati, JointControlli* controlli) 
{                                                                                                                                                      
    this->joints=joints;             //creo la funzione di init                                                        
    this->dati=dati;                 //e "scorro" nell'array passandogli                                      
    this->controlli=controlli;       //il valore di ogni pin                                       
    int i; 
    for(i=0;i<NUM_MOTORS; i++)
    {
        joints[i].init(dati[i].pins);
    }
}

void Ares_drive::move(double x, double y, double theta)  
{
    int r,j;                             
    double comp_vec[3] = {theta, x, y};  //creo la funzione "move" che è in grado di calcolare
    double speed = 0;                    //il valore di direzione, velocità ecc... di ogni motore 
    for(r=0;r<NUM_MOTORS;r++)            
    {                                    
        for(j=0;j<NUM_MOTORS;j++)       
        {
            speed+=ares_matrix[r][j]*comp_vec[j];
        }
        controlli[r].speed = (int16_t)(speed*255);
        speed=0;
    }
}

void Ares_drive::handle()  //imposto ogni valore che ho calcolato nella funzione "move" per ogni motore
{
    int i;
    for(i=0;i<NUM_MOTORS;++i) 
    {
    joints[i].setSpeed(controlli[i].speed);
    joints[i].handle();
    }
}
