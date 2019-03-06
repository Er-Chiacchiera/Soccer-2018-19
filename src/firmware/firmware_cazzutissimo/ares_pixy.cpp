/**
 * phoenix_pixy.cpp
 **/

#include "ares_pixy.h"

// Oggetto Pixy privato (nascosto all'esterno della libreria)
static Pixy pixy;

/**
 * Inizializza p (PhoenixCamera*) azzerando i valori
 * ball_detection, ball_x, ball_y, ball_w e ball_h
 * In oltre è necessario inizializzare 
 * l'oggetto pixy (Pixy) tramite il metodo pixy.init()
 **/
void PhoenixCamera_init(PhoenixCamera* p) 
{
  p->ball_detection = 0;
  p->ball_x = 0;
  p->ball_y = 0;
  p->ball_w = 0;
  p->ball_h = 0;
  pixy.init();
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
  uint8_t blocks_num = pixy.getBlocks();
  if(blocks_num >= 1)
  {
    for(int i=0;i<blocks_num;i++)
    {
      if(pixy.blocks[i].signature == BALL_SIG)
      {
        if(p->ball_detection < BALL_RELIABLE_CTR)
        {
          ++p->ball_detection;
        }
        dect_ball = 1;
        p->ball_x = pixy.blocks[i].x;
        p->ball_y = pixy.blocks[i].y;
        p->ball_w = pixy.blocks[i].width;
        p->ball_h = pixy.blocks[i].height;
      }
    }
    if(p->ball_detection > 0)
     {
       --p->ball_detection;
     }
  }
  else
  {
   if(p->ball_detection > 0)
   {
     --p->ball_detection;
   }
  }
  return;
}

/**
 * Restituisce il valore ball_detection
 **/
uint8_t PhoenixCamera_getBallStatus(PhoenixCamera* p) {
  return p->ball_detection;
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
  uint8_t NUM_BLOCKS = pixy.getBlocks();
  return NUM_BLOCKS;
}

