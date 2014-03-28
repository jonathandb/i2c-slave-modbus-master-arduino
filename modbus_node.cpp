#include "Arduino.h"
#include "modbus_node.h"
#include <ModbusMaster.h>

ModbusNode::ModbusNode(unsigned short address) {
  node.begin(address);
}

//success = true
bool ModbusNode::readDataFromClient(uint16_t *data, unsigned short reg) {
  uint8_t result;
  node.setTransmitBuffer(0, reg);
  result = node.readHoldingRegisters(2, 6);
  
  if(result == node.ku8MBSuccess) {
    for (unsigned short i = 0; i < 6; i++)
    {
      data[i] = node.getResponseBuffer(i);
    }
    return true;
  } else {
    return false;
  }
}
