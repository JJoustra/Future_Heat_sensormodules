/*
* DHTRead.cpp
* auteur: Amber Laci
* versie: 1.2
* Code bestand met de functies om de DHT22 sensoren uit te lezen.
*/
#include "DHTRead.h"

/**
 * @brief initialisatie functie voor de 3 DHT22 opnemers.
 */
void DHTInit ()
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

/**
 * @brief vult de globale struct "Package" (zie DHTRead.h) met de metingen van de sensoren.
 */
void DHTFillMsg()
{
    float T;
    float RH;
    for (int i = 0; i < 3; i++) 
    {
        T = Package[i].Sensor->readTemperature();
        RH = Package[i].Sensor->readHumidity();

        Package[i].Temperature = T;
        Package[i].Humidity = RH;
    }    
} 



