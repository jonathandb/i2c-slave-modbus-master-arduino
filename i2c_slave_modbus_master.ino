#include <arduino.h>
#include <MemoryFree.h>
#include <ModbusMaster.h>
#include <EEPROM.h>
#include "configuration.h"
#include "modbus_node.h"
#include <Wire.h>

enum State {
 noState,
 settingI2cAddress,
 settingParametersToReceive,
 settingModbusAddress,
 settingModbusRegister,
 readSensorValue,
 unknownDataReceived,
 readingConfigVersion
};

State state = settingParametersToReceive;
State previousState = noState;

unsigned short requestPosition = 0;


unsigned int modbusSlaveAddress = 0;
unsigned int modbusRegisterAddress = 0;

unsigned int readSensorvalue = 0;

bool readDataSuccess = false;

Configuration configuration;

//ModbusNode modbusNode(configuration.parameters.modbusAddress);


void setup() {
    //check configuration
    
    Serial.begin(9600);
    
    Wire.begin(configuration.parameters.i2cAddress);
    
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    
    
  }


void loop() {  
  
}

void receiveData(int byteCount) {
  unsigned int data;
  while(Wire.available()) {
    data = Wire.read();
    Serial.println(data);
    
    if(state == settingParametersToReceive) {
      requestPosition = 0;
    } else {
      requestPosition += 1;
    }
    
    switch(state)
    {
    case settingParametersToReceive:
      if(data == 224) {
        state = readingConfigVersion;
      } else if(data == 225) {
        state = settingModbusAddress;
      } else if(data == 226) {
        state = readSensorValue;
      } else {
        state = unknownDataReceived;
      }
      requestPosition = 0;
      break;
    case settingModbusAddress:
      modbusSlaveAddress = data;      
      state = settingModbusRegister;
      break;
    case settingModbusRegister:
      modbusRegisterAddress = data;
      state = settingParametersToReceive;
      break;
    case readSensorValue:
    
      break;
    default:
      break;
    }
    
    previousState = state;
  }
  
  Serial.println(requestPosition);
}

void sendData(){
  //Wire.write(200);
    switch(state)
    {
      case readingConfigVersion:
        Wire.write(configuration.parameters.programVersion[requestPosition]);
        if(requestPosition > 1) {
          state = settingParametersToReceive;
        }
        break;
      case readSensorValue:
        //readDataSuccess = modbusNode.readDataFromClient(&readSensorvalue, modbusRegisterAddress);
        
        //emulate modbus read
        Serial.println(requestPosition);
        if(requestPosition > 1000) {
          readDataSuccess = true;
        }
        requestPosition++;
        if(!readDataSuccess) {
          //send modbus read status
          Wire.write(0x0);
        }
        if(readDataSuccess && requestPosition > 5 ) {
          requestPosition = 0;
          Wire.write(0xff);
        }
        if(readDataSuccess && requestPosition == 1) {
          Wire.write(modbusSlaveAddress);
        } else if(readDataSuccess && requestPosition == 2) {
          Wire.write(modbusRegisterAddress);
          state = settingParametersToReceive;
          readDataSuccess = false;
        }
        break;
    }
}

unsigned short getModbusSensorData(unsigned short modbusAddress, unsigned short) {
  
}

unsigned short getI2cSensorData(unsigned short i2cSlaveAddress) {
  
}



