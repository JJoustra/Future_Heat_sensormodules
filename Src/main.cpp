#include "admin.h"

void setup() {
    pinMode(ONBOARD_LED, OUTPUT);

  /***************************paal module setup**************************/
  // digitalWrite(GND1, LOW);
  // digitalWrite(GND2, LOW);  //constraints in de hardware, meer 0V pins waren nodig, haal weg voor andere hardware
  // pinMode(DHTPIN10, INPUT_PULLUP);
  // pinMode(DHTPIN15, INPUT_PULLUP);
  // pinMode(DHTPIN20, INPUT_PULLUP);

  // DHTInit();
  // if (!connectWiFi(WIFI_SSID, WIFI_PASS)) error(NOWIFI);
  // if (!dbBegin(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD)) error(NODB);

  /***************************vloer module setup**************************/

  pinMode(DS18_PIN, INPUT_PULLUP);
  
  if (!WiFi.begin(WIFI_SSID, WIFI_PASS)); error(NOWIFI);
  if (!dbBegin(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD)); error(NODB);
  if (!ds18Begin()) error(NOSENS);

}

void loop() {
  /***************************paal module loop**************************/
  // for (uint8_t i = 0; i < 3; i++){
  //   if (!DHTFillMsg(i)) {error(NOSENS);}
      
  //  delay(MINUUT);
  // } 
  // if (!dbSendPaalDHT(
  //               Package[0].Temperature, 
  //               Package[0].Humidity, 
  //               Package[1].Temperature, 
  //               Package[1].Humidity, 
  //               Package[2].Temperature, 
  //               Package[2].Humidity, 
  //               DEVICE_ID
  //             )
  //     ); error(SENDFAIL);       


  /***************************vloer module loop**************************/
  
  float tempC;
  tempC = ds18Read(adres); 

  if (tempC == DEVICE_DISCONNECTED_C) {
    error(NOSENS);
    
    delay(MINUUT);
    return;
  }
  if (!dbSendFloorTemp(tempC, DEVICE_ID)); error(SENDFAIL);
  
  delay(MINUUT);

}