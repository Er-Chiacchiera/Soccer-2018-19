/**
 * phoenix_timer.h
 **/

#include <Arduino.h>
#include <avr/io.h>


struct Timer;

typedef void (*TimerFn)(void*);

void Timer_init(void);

struct Timer* Timer_create(uint16_t duration_ms,
                           TimerFn timer_fn,
                           void* timer_args);

void Timer_destroy(struct Timer*);
void Timer_start(struct Timer*);
void Timer_stop(struct Timer*);





