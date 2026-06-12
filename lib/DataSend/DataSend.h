#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <InfluxDbClient.h>

#define ONBOARD_LED 8
#ifndef INFLUXDB_URL
#define INFLUXDB_URL "http://192.168.1.31:8089"
#endif
#ifndef INFLUXDB_DB_NAME
#define INFLUXDB_DB_NAME "home"
#endif

static InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

bool connectWiFi(const char* ssid, const char* pass);
bool dbBegin(const char* dbURL, const char* dbName, const char* dbUser, const char* dbPassword);
bool dbSendFloorTemp(float tempC, const char* ID);
bool dbSendPaalDHT(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID);