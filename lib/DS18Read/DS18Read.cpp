/*
* DS18Read.cpp
* auteur: Stan Dam
* versie: 1.1
* Code bestand met de functies om de DS18B20 sensor uit te lezen.
*/
#include "DS18Read.h"

static OneWire oneWire(DS18_PIN);
static DallasTemperature sensors(&oneWire);

/**
 * @brief initialisatie functie voor de DS18B20 opnemer.
 */
void ds18Begin()
{
    sensors.begin();
}

/**
 * @brief schrijft de gemeten temperatuur (C) op het adres van de parameter tempC.
 * @param tempC floating point variabele waarnaar de temperatuur in graden Celsius geschreven wordt.
 * @return true of false voor of de meting succesvol was of niet.
 */
bool ds18Read(float &tempC)
{
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0);

    if (tempC == DEVICE_DISCONNECTED_C) return false;

    return true;
}