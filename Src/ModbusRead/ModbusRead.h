#pragma once
#include <Arduino.h>
#include <ModbusMaster.h>


#define MODBUS_DE_PIN   7
#define MODBUS_BAUD     9600 // AANPASSEN 38K4
#define SLAVE_ID        1

struct ControllerSnapshot {
    uint8_t stateRaw;              // register 4, 8 bits used

    uint16_t aanvoerTemperatuur;   // register 13
    uint16_t retourTemperatuur;    // register 14
    uint16_t condensWaarde;        // register 15

    uint8_t pompStatusRaw;         // register 127, 8 bits used

    bool valid;
};

class ModBusReader {
public:
    ModBusReader(HardwareSerial& serial, uint8_t dePin, uint32_t baud);

    void begin();

    uint16_t readRegister(uint8_t slaveId, uint16_t reg, bool& success);
    bool readRegisters(uint8_t slaveId, uint16_t startReg, uint8_t count, uint16_t dest[]);

    bool readControllerSnapshot(uint8_t slaveId, ControllerSnapshot& out);

private:
    static void preTransmission();
    static void postTransmission();
  

    HardwareSerial& _serial;
    uint8_t _dePin;
    uint32_t _baud;

    ModbusMaster _node;

    static ModBusReader* _instance;
};