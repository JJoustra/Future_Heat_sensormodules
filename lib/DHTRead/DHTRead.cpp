/*
* DHTRead.cpp
* auteur: Amber Laçi
* versie: 1.2
* Code bestand met de functies om de DHT22 sensoren uit te lezen.
*/
#include "DHTRead.h"

DHT DHT22_10(DHTPIN10, DHTTYPE);
DHT DHT22_15(DHTPIN15, DHTTYPE);
DHT DHT22_20(DHTPIN20, DHTTYPE);

DHT_DATA Package[3] = {
  {"DHT22_10", 0, 0},
  {"DHT22_15", 0, 0},
  {"DHT22_20", 0, 0}
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
 * @param i, tellervariabel omdat deze functie in main via een for loop wordt aangeroepen
 */
bool DHTFillMsg(uint8_t i)
{
    float T;
    float RH;
        if(i == 0){
            T = DHT22_10.readTemperature();
            RH = DHT22_10.readHumidity();
        } else if(i == 1){
            T = DHT22_15.readTemperature();
            RH = DHT22_15.readHumidity();
        } else if(i == 2){
            T = DHT22_20.readTemperature();
            RH = DHT22_20.readHumidity();
        }
        if (isnan(T) || isnan(RH)){
            return false;
        } else{
            Package[i].Temperature = T;
            Package[i].Humidity = RH;  
            return true;
        }

} 



