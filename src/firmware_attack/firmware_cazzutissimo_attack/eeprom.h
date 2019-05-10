/**
 * eeprom.h
 **/

#pragma once
#include <stdint.h>

/**
 * Initialize EEPROM module
 **/
void EEPROM_init(void);

/**
 * read from src, size bytes and stores them in dest_
 **/
void EEPROM_read(void* dest_, const uint16_t src, uint16_t size);

/**
 * write to dest, size bytes from src
 **/
void EEPROM_write(const uint16_t dest, void* src, uint16_t size);
