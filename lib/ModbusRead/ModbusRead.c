#include "ModbusRead.h"

// required for static callbacks
ModBusReader* ModBusReader::_instance = nullptr;

ModBusReader::ModBusReader(HardwareSerial& serial, uint8_t dePin, uint32_t baud)
// object aanmaken met de correcte pins
    : _serial(serial), _dePin(dePin), _baud(baud) {
    _instance = this;
}

void ModBusReader::begin() {
    //zet bordje op receive 
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
    
    
    _serial.begin(_baud, SERIAL_8N1, 4, 5);

    // zorg ervoor dat voor een bericht wordt verstuurt hij altijd op transmit gezet word, en andersom.
    _node.preTransmission(preTransmission);
    _node.postTransmission(postTransmission);

    Serial.println("[Modbus] Ready");
}

void ModBusReader::preTransmission() {
    // zet bordje op transmit
    if (_instance) digitalWrite(_instance->_dePin, HIGH);
}

void ModBusReader::postTransmission() {
    // zet bordje terug op receive
    if (_instance) digitalWrite(_instance->_dePin, LOW);
}

uint16_t ModBusReader::readRegister(uint8_t slaveId, uint16_t reg, bool& success) {
    // start communicatie met het bordje
    _node.begin(slaveId, _serial);

    // lees 1 register uit
    uint8_t result = _node.readHoldingRegisters(reg, 1);
    // check resultaat
    if (result == _node.ku8MBSuccess) {
        //als succesvol, zet success flag en haal de data op
        success = true;
        return _node.getResponseBuffer(0);
    }

    success = false;
    // als er een fout is, log het en return 0
    Serial.printf("[Modbus] Error reading slave %d reg %d — code: 0x%02X\n", slaveId, reg, result);
    return 0;
}

bool ModBusReader::readRegisters(uint8_t slaveId, uint16_t startReg, uint8_t count, uint16_t dest[]) {
    // start communicatie met het bordje
    _node.begin(slaveId, _serial);
    // lees meerdere registers uit
    uint8_t result = _node.readHoldingRegisters(startReg, count);

    if (result == _node.ku8MBSuccess) {
        // als succesvol, haal de data op
        for (uint8_t i = 0; i < count; i++) {
            //zet data in de array
            dest[i] = _node.getResponseBuffer(i);
        }
        return true;
    }

    // als er een fout is, log het en return false
    Serial.printf("[Modbus] Error reading slave %d regs %d-%d — code: 0x%02X\n",
                  slaveId, startReg, startReg + count - 1, result);
    return false;
}


bool ModBusReader::readControllerSnapshot(uint8_t slaveId, ControllerSnapshot& out) {
    ControllerSnapshot tmp{};
    bool ok = false;

    // register 4: 8-bit state
    uint16_t reg4 = readRegister(slaveId, 4, ok);
    if (!ok) return false;

    // alleen de onderste 8 bits zijn relevant
    tmp.stateRaw = (uint8_t)(reg4 & 0xFF);

    // registers 13, 14, 15: 16-bit values
    uint16_t regs[3];
    if (!readRegisters(slaveId, 13, 3, regs)) return false;

    // zet waarden in snapshot struct
    tmp.aanvoerTemperatuur = regs[0];
    tmp.retourTemperatuur  = regs[1];
    tmp.condensWaarde      = regs[2];

    // register 127: 8-bit pump output status
    uint16_t reg127 = readRegister(slaveId, 127, ok);
    if (!ok) return false;

    // alleen de onderste 8 bits zijn relevant
    tmp.pompStatusRaw = (uint8_t)(reg127 & 0xFF);

    // markeer snapshot als geldig en return hem 
    tmp.valid = true;
    out = tmp;
    return true;
} 