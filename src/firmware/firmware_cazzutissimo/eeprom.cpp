/**
 * eeprom.cpp
 **/

#include "eeprom.h"
#include <avr/eeprom.h>
#include <Arduino.h>

/**
 * Initialize EEPROM module
 **/
void EEPROM_init(void) {
  return;
}

/**
 * read from src, size bytes and stores them in dest_
 **/
void EEPROM_read(void* dest_, const uint16_t src, uint16_t size) {
  uint8_t* dest=(uint8_t*)dest_;
  uint16_t s=src;
  for(int i=0;i<size;++i) {
    eeprom_busy_wait();
    *dest=eeprom_read_byte(s);
    ++dest;
    ++s;
  }
}

/**
 * write to dest, size bytes from src
 **/
void EEPROM_write(const uint16_t dest, void* src, uint16_t size) {
  uint16_t d=(uint16_t)dest;
  uint8_t* s=(uint8_t*)src;
  for(int i=0;i<size;++i) {
    eeprom_busy_wait();
    eeprom_write_byte(d, *s);
    ++s;
    ++d;
  }
}
