/*
* DS18Read.cpp
* auteur: Stan Dam
* versie: 1.1
* Code bestand met de functies om de DS18B20 sensor uit te lezen.
*/
#include "DS18Read.h"

DeviceAddress adres;
static OneWire oneWire(DS18_PIN);
static DallasTemperature sensors(&oneWire);

/**
 * @brief initialisatie functie voor de DS18B20 opnemer.
 */
bool ds18Begin()
{
    sensors.begin();

     oneWire.reset_search();
     if (!oneWire.search(adres)) return false;
     return true;
}

/**
 * @brief schrijft de gemeten temperatuur (C) op het adres van de parameter tempC.
 * @param tempC floating point variabele waarnaar de temperatuur in graden Celsius geschreven wordt.
 * @return true of false voor of de meting succesvol was of niet.
 */
float ds18Read(DeviceAddress adres)
{
    sensors.requestTemperatures();
    float tempC = sensors.getTempC(adres);


    return tempC;
}