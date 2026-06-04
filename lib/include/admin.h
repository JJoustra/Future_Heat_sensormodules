/***************************Paal module includes en defines**************************/
static const char WIFI_SSID[] = "PLACEHOLDER";
static const char WIFI_PASS[] = "PLACEHOLDER";
static const char INFLUXDB_URL[] = "http://PLACEHOLDER:PLACEHOLDER";
static const char INFLUXDB_DB_NAME[] = "PLACEHOLDER";
static const char INFLUXDB_USER[] = "admin";
static const char INFLUXDB_PASSWORD[] = "PLACEHOLDER";

#include "DHTRead.h"
#include <Arduino.h>
#include "DataSend.h"
#include "ErrorHandler.h"

static const char DEVICE_ID[] = "P01"; // unieke ID per module VERGEET NIET OM AAN TE PASSEN
#define NOWIFI 1
#define NODB 8
#define NOSENS 3
#define MINUUT 60000

/***************************vloer module includes en defines**************************/
// #define WIFI_SSID "PLACEHOLDER"
// #define WIFI_PASS "PLACEHOLDER"
// #define INFLUXDB_URL "http://PLACEHOLDER:PLACEHOLDER"
// #define INFLUXDB_DB_NAME "PLACEHOLDER"
// #define INFLUXDB_USER "admin"
// #define INFLUXDB_PASSWORD "PLACEHOLDER"
// #define MINUUT 60000

// #include "DS18Read.h"
// #include <Arduino.h>
// #include "DataSend.h"
// #define DEVICE_ID "V01" // unieke ID per module VERGEET NIET OM AAN TE PASSEN