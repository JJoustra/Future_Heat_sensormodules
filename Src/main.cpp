#include <Arduino.h>
#include "DataBaseVerstuur.h"
#include "DS18Read.h"
#include "DHTRead.h"


    DhtPack paalData = {};
    float vloerTemp = 0;
    
void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("Boot");

    ds18Begin();
    dhtBegin();

    if (!dbBegin())
    {
        Serial.println("Database init failed");
    }
}

void loop()
{

    ds18Read(vloerTemp);
    dhtRead(paalData);
    

   
        Serial.print("Vloer temp: ");
        Serial.println(vloerTemp);
        dbSendFloorTemp(vloerTemp, "V01");


        Serial.print("T10: "); Serial.print(paalData.t10);
        Serial.print(" RH10: "); Serial.println(paalData.h10);

        Serial.print("T15: "); Serial.print(paalData.t15);
        Serial.print(" RH15: "); Serial.println(paalData.h15);

        Serial.print("T20: "); Serial.print(paalData.t20);
        Serial.print(" RH20: "); Serial.println(paalData.h20);

        dbSendPaalDht(
            paalData.t10, paalData.h10,
            paalData.t15, paalData.h15,
            paalData.t20, paalData.h20,
            "P01"
        );

    delay(10000);
}