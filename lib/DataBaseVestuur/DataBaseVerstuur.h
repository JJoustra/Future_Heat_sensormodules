#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <InfluxDbClient.h>

bool dbBegin();
bool dbSendFloorTemp(float tempC, const char* ID);
bool dbSendPaalDht(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID);