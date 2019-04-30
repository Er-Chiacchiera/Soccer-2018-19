/**
 * phoenix_eeprom.cpp
 **/

#include "ares_eeprom.h"
#include "eeprom.h"
#include "ares_globals.h"
#include "ares_params.h"

#define LINESENSOR_OFFSET 32


void PhoenixEeprom_init(void) {
  EEPROM_init();
  return;
}

void PhoenixEeprom_storeLineSensor(void) {
  EEPROM_write(LINESENSOR_OFFSET, (void*)line_sensors,
               sizeof(PhoenixLineSensor)*NUM_LINE_SENSORS);
}

void PhoenixEeprom_loadLineSensor(void) {
  EEPROM_read((void*)line_sensors, LINESENSOR_OFFSET,
              sizeof(PhoenixLineSensor)*NUM_LINE_SENSORS);
}

