// Stores and reads meter from EEPROM

#include <EEPROM.h>
int addr = 0;

#define EEPROM_SIZE 32 // Float is 8 bytes and we only store a single float for now

/**
 * Loads reading from EEPROM
 */
float load_meter() {
  float meter_read = -1;

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(addr, meter_read);
  EEPROM.end();

  return meter_read;
}

/**
 * Saves reading in EEPROM
 */
void save_meter(float meter_read) {
  EEPROM.begin(EEPROM_SIZE);

  EEPROM.put(addr, meter_read);

  EEPROM.commit();

  EEPROM.end();
}

/**
 * Indicate that every second whole cubic meter the state should be updated in storage.
 *
 * EEPROM write lifetime limited to few thousands (10.000 - 100.000)
 */ 
bool save_meter() {
  int meter_rnd = ceil(global_meter);

  bool do_save =  abs( meter_rnd - global_meter) < 0.01 && meter_rnd % 2 == 0;

  return do_save;
}