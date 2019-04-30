/**
 * phoenix_timer.cpp
 **/

#include "ares_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_TIMERS 8

/**
 * IMPORTANTE DA LEGGERE:
 * Le funzioni che scrivete qui sotto sono molto sensibili e non devono
 * essere interrotte durante la loro esecuzione (per esempio a causa di un
 * interrupt dei timer stessi).
 * Per questo all'inizio di ogni funzione viene lanciata la funzione
 * cli() [CLear Interrupt] che disattiva gli interrupt del microcontrollore.
 * Alla fine della funzione viene poi lanciata
 * sei() [SEt Interrupt] che riattiva gli interrupt del microcontrollore.
 **/


static uint8_t mask_read(uint8_t* mask, uint8_t index) {
  return (*mask & (0x1<<index))!=0;
}

static void mask_set(uint8_t* mask, uint8_t index) {
  *mask |= (0x1<<index);
  return;
}

static void mask_clear(uint8_t* mask, uint8_t index) {
  *mask &= ~(0x1<<index);
  return;
}

typedef struct Timer{
  uint8_t stop_flag;
  uint16_t duration_ms;
  TimerFn fn;
  uint8_t timer_num;
  void* args;
}Timer;

uint8_t timers_mask=0;
Timer timers[NUM_TIMERS];

/**
 * Utilizza TIMER5 per inviare un interrupt
 * ogni millisecondo
 **/
void Timer_init() {
  cli();
  TCCR5A=0;
  TCCR5B=0;

  // CTC-Mode | Prescaler=8 => clock_period=0.5uS
  TCCR5B=(1<<WGM12) | (1<<CS51);
  // To achieve 1ms period we need OCR5A to be 1999 (1000 ms / 0.5 us - 1 = 1999 )
  OCR5A=1999;
  // Enable Timer Output Compare A interrupt mask on TIMSK5
  TIMSK5|=(1<<OCIE5A);

  sei();
  
}

/**
 * Crea una nuova istanza di Timer con duration_ms,
 * stop_flag pari ad 1, fn pari a timer_fn
 * e args pari a timer_args
 * Nel file .cpp è già presente un array di Timer(s)
 * Per controllare quale posizione è già stata allocata
 * devi controllare la maschera (timers_mask).
 * Se il bit i-esimo della maschera e' pari a 0
 * allora la cella i-esima dell'array è vuota.
 * Inoltre imposta la variabile timer_num pari ad i
 * Una volta riempita la struttura, ricordati di impostare
 * il bit i-esimo della maschera ad 1
 **/
struct Timer* Timer_create(uint16_t duration_ms,
                           TimerFn timer_fn,
                           void* timer_args) {
  cli();// Disattiva interrupt
  for(int i=0;i<NUM_TIMERS;i++)
  {
    if(mask_read(&timers_mask, i) == 0)
    {
      timers[i].duration_ms = duration_ms;
      timers[i].stop_flag = 1;
      timers[i].fn = timer_fn;
      timers[i].args = timer_args; 
      timers[i].timer_num = i;
      mask_set(&timers_mask, i);
      sei();
      return &timers[i];
    }
  }
  sei();// Attiva interrupt
  return 0; // Non ci sono slot disponibili
}

/**
 * Azzera il bit t->timer_num esimo della
 * maschera timers_mask 
 **/
void Timer_destroy(struct Timer* t) {
  cli();
  mask_clear(&timers_mask, t->timer_num);
  sei();
}

/**
 * Imposta a 0 la variabile stop_flag di t
 **/
void Timer_start(struct Timer* t) {
  cli();
  t->stop_flag = 0;
  sei();
}

/**
 * Imposta a 1 la variabile stop_flag di t
 **/
void Timer_stop(struct Timer* t) {
  cli();
  t->stop_flag = 1;
  sei();
}

// variabile che tiene conto dei millisecondi passati
volatile uint16_t elapsed_time=0;

/**
 * ISR (Interrupt Service Routine)
 * e' una funzione speciale che viene eseguita quando si verifica
 * un determinato interrupt (TIMER5_COMPA_vect : quando il contatore
 * di TIMER5 raggiunge il valore di OCR5A (1999), viene lanciato 
 * l'interrupt).
 * Queste funzioni devono essere molto veloci e corte in quanto vengono
 * eseguite spesso ( di fatto 1000 volte al secondo ).
 *
 * Nello specifico questa ISR dovrà:
 * 
 * 0) incrementare di 1 la variabile elapsed_time (elapsed_time++)
 * 1) scannerizzare uno alla volta i NUM_TIMERS timer(s) in cerca
 *    dei timer attivi (ricavabili attraverso la maschera)
 * 2) controllare che la stop_flag sia pari a 0 (quindi il timer sia attivo)
 * 3) Che (elapsed_time % duration_ms) sia pari a 0 (ovvero che 
 *    sia il momento giusto di lanciare la funzione del timer)
 * 
 * Se le condizioni sopra sono verificate allora esegue il comando
 * (*timers[i].fn)(timers[i].args);
 * dove i è l'indice del timer attivo corrente da eseguire
 * Questo comando lancia l'esecuzione della funzione 
 * associata al timer, passando i parametri args
 **/
ISR(TIMER5_COMPA_vect) {  //(elapsed_time%timers[i].duration_ms == 0)
  elapsed_time++;
  for(int i=0;i<NUM_TIMERS;i++)
  {
    mask_read(&timers_mask, i);
    if(mask_read(&timers_mask, i) == 1)
    {
      if(timers[i].stop_flag == 0)
      {
        if(elapsed_time%timers[i].duration_ms == 0) 
        {
          (*timers[i].fn)(timers[i].args);
        }
      }
    }
  }
}
