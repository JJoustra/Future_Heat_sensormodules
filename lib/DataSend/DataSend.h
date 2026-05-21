#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <InfluxDbClient.h>

#define WIFI_SSID "H220N10CA01"
#define WIFI_PASS "DD5F77EA1E95"

#define INFLUXDB_URL "http://192.168.2.15:8086"
#define INFLUXDB_DB_NAME "home"
#define INFLUXDB_USER "admin"
#define INFLUXDB_PASSWORD "password123"

static InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

bool dbBegin();
bool dbSendFloorTemp(float tempC, const char* ID);
bool dbSendPaalDht(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID);