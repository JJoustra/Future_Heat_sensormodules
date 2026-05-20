#include "DS18Read.h"

#define DS18_PIN 5

static OneWire oneWire(DS18_PIN);
static DallasTemperature sensors(&oneWire);

void ds18Begin()
{
    sensors.begin();
}

bool ds18Read(float &tempC)
{
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C)
        return false;

    return true;
}
