#include "ModbusRead.h"

ModBusReader* ModBusReader::_instance = nullptr;

ModBusReader::ModBusReader(HardwareSerial& serial, uint8_t dePin, uint32_t baud)
    : _serial(serial), _dePin(dePin), _baud(baud)
{
    _instance = this;
}

void ModBusReader::begin()
{
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);

    _serial.begin(_baud, SERIAL_8N1, 4, 5);

    _node.preTransmission(preTransmission);
    _node.postTransmission(postTransmission);

    Serial.println("[Modbus] Ready");
}

void ModBusReader::preTransmission()
{
    if (_instance) digitalWrite(_instance->_dePin, HIGH);
}

void ModBusReader::postTransmission()
{
    if (_instance) digitalWrite(_instance->_dePin, LOW);
}

uint16_t ModBusReader::readRegister(uint8_t slaveId, uint16_t reg, bool& success)
{
    _node.begin(slaveId, _serial);

    uint8_t result = _node.readHoldingRegisters(reg, 1);
    if (result == _node.ku8MBSuccess)
    {
        success = true;
        return _node.getResponseBuffer(0);
    }

    success = false;
    Serial.printf("[Modbus] Error reading slave %d reg %d - code: 0x%02X\n", slaveId, reg, result);
    return 0;
}

bool ModBusReader::readRegisters(uint8_t slaveId, uint16_t startReg, uint8_t count, uint16_t dest[])
{
    _node.begin(slaveId, _serial);

    uint8_t result = _node.readHoldingRegisters(startReg, count);
    if (result == _node.ku8MBSuccess)
    {
        for (uint8_t i = 0; i < count; i++)
        {
            dest[i] = _node.getResponseBuffer(i);
        }
        return true;
    }

    Serial.printf("[Modbus] Error reading slave %d regs %d-%d - code: 0x%02X\n",
                  slaveId, startReg, startReg + count - 1, result);
    return false;
}

bool ModBusReader::readControllerSnapshot(uint8_t slaveId, ControllerSnapshot& out)
{
    ControllerSnapshot tmp{};
    bool ok = false;

    uint16_t reg4 = readRegister(slaveId, 4, ok);
    if (!ok) return false;

    tmp.stateRaw = (uint8_t)(reg4 & 0xFF);

    uint16_t regs[3];
    if (!readRegisters(slaveId, 13, 3, regs)) return false;

    tmp.aanvoerTemperatuur = regs[0];
    tmp.retourTemperatuur = regs[1];
    tmp.condensWaarde = regs[2];

    uint16_t reg127 = readRegister(slaveId, 127, ok);
    if (!ok) return false;

    tmp.pompStatusRaw = (uint8_t)(reg127 & 0xFF);
    tmp.valid = true;
    out = tmp;
    return true;
}
