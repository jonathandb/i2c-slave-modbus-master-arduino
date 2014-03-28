#include "Arduino.h"
#include <Wire.h>

class I2cNode {
private:

public:
  I2cNode();
  void initClient(unsigned short address);
  void readPortFromClient(unsigned short address, char p);
  
};
