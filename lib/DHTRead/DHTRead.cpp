#include <Arduino.h>
#include <DHT.h>
#include "DHTRead.h"

#define DHTTYPE DHT11

#define DHTPIN_10 2
#define DHTPIN_15 3
#define DHTPIN_20 4

static DHT dht10(DHTPIN_10, DHTTYPE);
static DHT dht15(DHTPIN_15, DHTTYPE);
static DHT dht20(DHTPIN_20, DHTTYPE);

void dhtBegin()
{
    dht10.begin();
    dht15.begin();
    dht20.begin();
}

static bool validReading(float t, float h)
{
    return !isnan(t) && !isnan(h);
}

bool dhtRead(DhtPack &data)
{
    data.t10 = dht10.readTemperature();
    data.h10 = dht10.readHumidity();

    data.t15 = dht15.readTemperature();
    data.h15 = dht15.readHumidity();

    data.t20 = dht20.readTemperature();
    data.h20 = dht20.readHumidity();

    if (!validReading(data.t10, data.h10)) return false;
    if (!validReading(data.t15, data.h15)) return false;
    if (!validReading(data.t20, data.h20)) return false;

    return true;
}
