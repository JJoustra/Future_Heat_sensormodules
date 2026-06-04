#include "admin.h"

void setup() {
    pinMode(ONBOARD_LED, OUTPUT);

  /***************************paal module setup**************************/
  DHTInit();
  if (!connectWiFi(WIFI_SSID, WIFI_PASS)) {error(NOWIFI);}
  if (!dbBegin(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD)) {error(NODB);}

  /***************************vloer module setup**************************/
  // ds18Begin();
  // pinMode(DS18_PIN, PULLUP);
  // digitalWrite(21, LOW);
  // if (!WiFi.begin(WIFI_SSID, WIFI_PASS)); //error(NOWIFI);
  // if (!dbBegin(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD)); //error(NODB);

}

void loop() {
  /***************************paal module loop**************************/
  // DHTFillMsg();
  // dbSendPaalDHT(
  //               Package[0].Temperature, 
  //               Package[0].Humidity, 
  //               Package[1].Temperature, 
  //               Package[1].Humidity, 
  //               Package[2].Temperature, 
  //               Package[2].Humidity, 
  //               DEVICE_ID
  //             );

  /***************************vloer module loop**************************/
  // float tempC;
  // ds18Read(tempC);
  // dbSendFloorTemp(tempC, DEVICE_ID);

  //delay(MINUUT);
}