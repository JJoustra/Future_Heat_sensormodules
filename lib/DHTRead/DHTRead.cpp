/*
* DHTRead.cpp
* auteur: Amber Laçi
* versie: 1.2
* Code bestand met de functies om de DHT22 sensoren uit te lezen.
*/
#include "DHTRead.h"

DHT DHT22_10(PIN10, DHT22);
DHT DHT22_15(PIN15, DHT22);
DHT DHT22_20(PIN20, DHT22);

DHT_DATA Package[3] = {
  {"DHT22_10", &DHT22_10, 0, 0},
  {"DHT22_15", &DHT22_15, 0, 0},
  {"DHT22_20", &DHT22_20, 0, 0}
};

/**
 * @brief initialisatie functie voor de 3 DHT22 opnemers.
 */
void DHTInit ()
{
    DHT22_10.begin();
    DHT22_15.begin();
    DHT22_20.begin();
}

/**
 * @brief vult de globale struct "Package" met de metingen van de sensoren.
 */
bool DHTFillMsg()
{
    float T;
    float RH;
    for (int i = 0; i < 3; i++) 
    {
        T = Package[i].Sensor->readTemperature();
        RH = Package[i].Sensor->readHumidity();
        if (isnan(T)) return false;
        if (isnan(RH)) return false;

        Package[i].Temperature = T;
        Package[i].Humidity = RH;
    }    
    return true;
} 



