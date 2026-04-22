#pragma once
#include <DHT.h>


enum DHT_Error {
    DHT_OK = 0,
    TEMP_NAN = 1,
    TEMP_RANGE = 2,
    HUM_NAN = 3,
    HUM_RANGE = 4
};

struct DHT_DATA {
    DHT* sensor;
    float Temperature;
    float Humidity;
    float error;
};

extern DHT_DATA Package[3];

char ErrorHandling(float temperature, float humidity);
void DHT_READ();
void DHT_INIT();