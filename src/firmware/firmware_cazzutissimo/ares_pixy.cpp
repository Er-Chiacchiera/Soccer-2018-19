/**
 * phoenix_pixy.cpp
 **/

#include "ares_pixy.h"
#include "utils.h"
#include <Pixy2I2C.h>

// Oggetto Pixy privato (nascosto all'esterno della libreria)
Pixy2I2C pixy;

/**
 * Inizializza p (PhoenixCamera*) azzerando i valori
 * ball_detection, ball_x, ball_y, ball_w e ball_h
 * In oltre è necessario inizializzare 
 * l'oggetto pixy (Pixy) tramite il metodo pixy.init()
 **/
void PhoenixCamera_init(PhoenixCamera* p) 
{
  pixy.init();
  p->ball_detection = 0;
  p->ball_x = 0;
  p->ball_y = 0;
  p->ball_w = 0;
  p->ball_h = 0;
  p->ball_age = 0;
  return;
}

/**
 * Interroga il modulo pixy, richiedendo il numero di blocchi
 * visti.
 * I passi necessari sono questi:
 * 1) Imposta ball_detection pari a 0
 * 2) Richiede numero di blocchi visti (pixy.getBlocks())
 * 3) Se almeno un blocco è stato rilevato, bisogna controllare
 *    se uno dei blocchi ha la stessa "signature" della palla
 *    (salvata in BALL_SIG) allora bisogna incrementare
 *    la variabile ball_detection;
 *    La variabile in questione deve essere limitata all'intervallo
 *    (0, BALL_RELIABLE_CTR)
 * 4) Una volta trovata la palla, scaricare i seguenti valori
 *    dalla pixy:
 *    - x (coordinata x del blocco)
 *    - y (coordinata y del blocco)
 *    - w (larghezza del blocco [width])
 *    - h (altezza x del blocco [height])
 * 5) Se non viene rilevato nessun blocco oppure non viene rilevata
 *    la palla, decrementare la variabile ball_detection
 **/
void PhoenixCamera_handle(PhoenixCamera* p) {
  uint8_t dect_ball=0;// variabile temporanea
  p->ball_detection = 0;
  uint8_t blocks_num = pixy.ccc.getBlocks();
  if(blocks_num > 0)
  {

    for(int i=0;i<blocks_num;i++)
    {
      if(pixy.ccc.blocks[i].m_signature == BALL_SIG)
      {
        p->ball_age = pixy.ccc.blocks[i].m_age;
        if(p->ball_age > BALL_RELIABLE_AGE){
          p->ball_x = pixy.ccc.blocks[i].m_x;
          p->ball_y = pixy.ccc.blocks[i].m_y;
          p->ball_w = pixy.ccc.blocks[i].m_width;
          p->ball_h = pixy.ccc.blocks[i].m_height;
          p->ball_detection = 1;
          p->area_ball = p->ball_w * p->ball_h;
          /*Serial.print("Area della palla:");
          Serial.println(p->area_ball);*/
          p->errore = (int16_t)p->ball_x - 160;
          p->errore = cconstrain(p->errore, 180, -180);

          double e_p = p->errore * p->kp;
          double e_d = p->kd*(p->errore - p->errore_prec)*p->idt;
          p->sum_i += p->ki*p->errore*p->dt;
          p->sum_i = clamp(p->sum_i, p->max_i);
          p->output_pid_camera = e_p + e_d + p->sum_i;
          p->output_pid_camera = clamp(p->output_pid_camera, p->max_output);
          p->errore_prec = p->errore;
        }
      }
      if(pixy.ccc.blocks[i].m_signature == DOOR_SIG)
      {
        p->door_age = pixy.ccc.blocks[i].m_age;
        if(p->door_age > DOOR_RELIABLE_AGE){
          p->door_x = pixy.ccc.blocks[i].m_x;
          p->door_y = pixy.ccc.blocks[i].m_y;
          p->door_w = pixy.ccc.blocks[i].m_width;
          p->door_h = pixy.ccc.blocks[i].m_height;
          p->door_detection = 1;
          p->area_door = p->door_w * p->door_h;
          /*Serial.print("Area della porta:");
          Serial.println(p->area_door);*/
        }
      }
    }
  return;
  }
}




/**
 * Restituisce il valore ball_detection
 **/
uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p) {
  return p->ball_detection;
}

uint8_t PhoenixCamera_getDoorStatus(PhoenixCamera* p){
  return p->door_detection;
}

/**
 * Restituisce il valore ball_x
 **/
uint16_t PhoenixCamera_getBallX(PhoenixCamera* p) {
  return p->ball_x;
}

/**
 * Restituisce il valore ball_y
 **/
uint16_t PhoenixCamera_getBallY(PhoenixCamera* p) {
  return p->ball_y;
}

/**
 * Restituisce il valore ball_w
 **/
uint16_t PhoenixCamera_getBallW(PhoenixCamera* p) {
  return p->ball_w;
}

/**
 * Restituisce il valore ball_h
 **/
uint16_t PhoenixCamera_getBallH(PhoenixCamera* p) {
  return p->ball_h;
}
/**
 * Restituisce il valore dei blocchi visti
 **/
uint16_t PhoenixCamera_getBlocks(PhoenixCamera* p){
   uint8_t NUM_BLOCKS = pixy.ccc.getBlocks();
  return NUM_BLOCKS;
}


uint8_t PhoenixCamera_getBallAge(PhoenixCamera * p){
  return p->ball_age;
}

uint8_t PhoenixCamera_getDoorAge(PhoenixCamera * p){
  return p->door_age;
}


