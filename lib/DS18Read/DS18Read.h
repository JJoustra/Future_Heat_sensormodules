#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

void ds18Begin();
bool ds18Read(float &tempC);
