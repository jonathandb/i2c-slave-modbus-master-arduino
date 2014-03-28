/* Based on http://playground.arduino.cc/Code/EEPROMLoadAndSaveSettings footswitch 2012-03-05

 */
#include "configuration.h"
#include "EEPROM.h"
#include "string.h"

Configuration::Configuration() {
  loadConfig();
}

void Configuration::loadConfig() {
  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (//EEPROM.read(CONFIG_START + sizeof(programVersion) - 1) == parameters.programVersion[3] // this is '\0'
      EEPROM.read(CONFIG_START + sizeof(parameters) - 2) == CONFIG_VERSION[2] &&
      EEPROM.read(CONFIG_START + sizeof(parameters) - 3) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + sizeof(parameters) - 4) == CONFIG_VERSION[0])
  { // reads settings from EEPROM
    for (unsigned int t=0; t<sizeof(parameters); t++) {
      *((char*)&parameters + t) = EEPROM.read(CONFIG_START + t);
    }
    loadSuccess = true;
  } else {
    // settings aren't valid! will overwrite with default settings
    saveDefaultConfig();
    loadSuccess = false;
  }
}

void Configuration::saveDefaultConfig() {
  parameters.modbusAddress = 1;
  parameters.i2cAddress = 0x04;
  strcpy(parameters.programVersion, CONFIG_VERSION);
  saveConfig();
}

void Configuration::saveConfig() {
  for (unsigned int t=0; t<sizeof(parameters); t++)
  { // writes to EEPROM"
    EEPROM.write(CONFIG_START + t, *((char*)&parameters + t));
    // and verifies the data
    if (EEPROM.read(CONFIG_START + t) != *((char*)&parameters + t))
    {
      // error writing to EEPROM
    }
  }
}

void Configuration::parseJsonConfig() {
  
}


