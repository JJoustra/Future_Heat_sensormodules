#include <Arduino.h>
#include "DHTRead.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Sensor ");
}

void loop() {
  //als ik hier meer dan 10 regels zie dan doe ik jullie wat aan
   Serial.print("Sensor ");
  DHT_READ();
  for (int i = 0; i < 3; i++) {
    Serial.print("Sensor ");
    /*Serial.print(i);
    Serial.println(":");
    
    Serial.print("Temperatuur: ");
    Serial.println(Package[i].Temperature);

    Serial.print("Humidity: ");
    Serial.println(Package[i].Humidity);
    Serial.println("-------------------");*/
  }
  delay(2000);
}