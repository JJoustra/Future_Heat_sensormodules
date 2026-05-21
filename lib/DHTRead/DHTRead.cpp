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
{
    DHT22_10.begin();
    DHT22_15.begin();
    DHT22_20.begin();
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



