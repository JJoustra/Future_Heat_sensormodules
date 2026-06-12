#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

#define DS18_PIN 20


extern DeviceAddress adres;
bool ds18Begin();
float ds18Read(DeviceAddress adres);