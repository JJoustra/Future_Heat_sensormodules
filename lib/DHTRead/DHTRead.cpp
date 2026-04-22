#include "DHTRead.h"

DHT DHT22_10(2, DHT22);
DHT DHT22_15(3, DHT22);
DHT DHT22_20(4, DHT22);

DHT_DATA Package[3] = {
  {&DHT22_10, 0, 0, 0},
  {&DHT22_15, 0, 0, 0},
  {&DHT22_20, 0, 0, 0},
};

char ErrorHandling(float temperature, float humidity)
{
    if (isnan(temperature)) return TEMP_NAN;
    if (temperature > 80 || temperature < -40) return TEMP_RANGE;
    if (isnan(humidity)) return HUM_NAN;
    if (humidity > 100 || humidity < 0) return HUM_RANGE;

    return DHT_OK;
}

void DHT_INIT ()
{
    DHT22_10.begin();
    DHT22_15.begin();
    DHT22_20.begin();
}

void DHT_READ()
{
    float T;
    float RH;
    for (int i = 0; i < 3; i++) 
    {
        T = Package[i].sensor->readTemperature();
        RH = Package[i].sensor->readHumidity();

        Package[i].Temperature = T;
        Package[i].Humidity = RH;
        Package[i].error = ErrorHandling(T, RH);
    }    
} 

