
#include "Arduino.h"
#include <EEPROM.h>

// Tell it where to store config data in EEPROM
#define CONFIG_START 32
#define CONFIG_VERSION "bl1" //must be 3 characters!!!!!!!!!!


typedef struct ConfigurationParameters {
  unsigned short modbusAddress;
  char i2cAddress;
  char programVersion[4];
};

class Configuration {
  private:
    void saveDefaultConfig();
  public:
    bool loadSuccess;
    ConfigurationParameters parameters;
    Configuration();
    void loadConfig();
    void saveConfig();
    void parseJsonConfig();
};
