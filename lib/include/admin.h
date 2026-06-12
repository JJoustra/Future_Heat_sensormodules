/***************************Paal module includes en defines**************************/
// static const char WIFI_SSID[] = "3DmakerszoneGast";
// static const char WIFI_PASS[] = "3DMZwelk0m!";
// static const char INFLUXDB_URL[] = "http://192.168.1.31:8089";
// static const char INFLUXDB_DB_NAME[] = "home";
// static const char INFLUXDB_USER[] = "admin";
// static const char INFLUXDB_PASSWORD[] = "password123";

// #include "DHTRead.h"
// #include <Arduino.h>
// #include "DataSend.h"
// #include "ErrorHandler.h"

// static const char DEVICE_ID[] = "P06"; // unieke ID per module VERGEET NIET OM AAN TE PASSEN
// #define GND1 4
// #define GND2 9
// #define NOWIFI 1
// #define NODB 2
// #define NOSENS 3
// #define SENDFAIL 4
// #define MINUUT 20000

/***************************vloer module includes en defines**************************/
static const char WIFI_SSID[] = "3DmakerszoneGast";
static const char WIFI_PASS[] = "3DMZwelk0m!";
static const char INFLUXDB_URL[] = "http://192.168.1.31:8089";
static const char INFLUXDB_DB_NAME[] = "home";
static const char INFLUXDB_USER[] = "admin";
static const char INFLUXDB_PASSWORD[] = "password123";

#include "DS18Read.h"
#include <Arduino.h>
#include "DataSend.h"
#include "ErrorHandler.h"
#define DEVICE_ID "V09" // unieke ID per module VERGEET NIET OM AAN TE PASSEN

#define GND1 21
#define NOWIFI 1
#define NODB 2
#define NOSENS 3
#define SENDFAIL 4
#define MINUUT 60000