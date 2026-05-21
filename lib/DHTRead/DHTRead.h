#include <DHT.h>
#define DHT22 22

//DHT package opbouw
struct DHT_DATA {
    const char* SensorNaam;
    DHT* Sensor;
    float Temperature;
    float Humidity;
};

//package declaratie
DHT DHT22_10(2, DHT22);
DHT DHT22_15(3, DHT22);
DHT DHT22_20(4, DHT22);

DHT_DATA Package[3] = {
  {"DHT22_10", &DHT22_10, 0, 0},
  {"DHT22_15", &DHT22_15, 0, 0},
  {"DHT22_20", &DHT22_20, 0, 0}
};

void DHTFillMsg();
void DHTInit();