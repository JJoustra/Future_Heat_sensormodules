#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

#define DS18_PIN 20

void ds18Begin();
bool ds18Read(float &tempC);