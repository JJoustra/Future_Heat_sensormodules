#pragma once
#include <DHT.h>
#define DHT22 22
#define DHTPIN10 10
#define DHTPIN15 20
#define DHTPIN20 21

//DHT package opbouw
struct DHT_DATA {
    const char* SensorNaam;
    DHT* Sensor;
    float Temperature;
    float Humidity;
};

//sensoren declaratie
extern DHT DHT22_10;
extern DHT DHT22_15;
extern DHT DHT22_20;

extern DHT_DATA Package[3];

bool DHTFillMsg();
void DHTInit();