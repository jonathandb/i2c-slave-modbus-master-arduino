#include "Arduino.h"
#include <ModbusMaster.h>



class ModbusNode {
  private:
    ModbusMaster node;
  public:
    ModbusNode(unsigned short address);
    void initClient();
    bool readDataFromClient(uint16_t *data, unsigned short register);

};
