#pragma once
#include <DHT.h>
#define DHT22 22
#define PIN10 2
#define PIN15 3
#define PIN20 4

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