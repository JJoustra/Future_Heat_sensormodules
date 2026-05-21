#include "DataBaseVerstuur.h"


static const char* WIFI_SSID = "H220N10CA01";
static const char* WIFI_PASS = "DD5F77EA1E95";

static const char* INFLUXDB_URL = "http://192.168.2.15:8086";
static const char* INFLUXDB_DB_NAME = "home";
static const char* INFLUXDB_USER = "admin";
static const char* INFLUXDB_PASSWORD = "password123";


static InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

static bool connectWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
    Serial.print("Connecting to WiFi");

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 20000)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi failed");
        return false;
    }

    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
    return true;
}

bool dbBegin()
{
    if (!connectWiFi())
        return false;

    client.setConnectionParamsV1(
        INFLUXDB_URL,
        INFLUXDB_DB_NAME,
        INFLUXDB_USER,
        INFLUXDB_PASSWORD
    );

    if (!client.validateConnection())
    {
        Serial.print("InfluxDB failed: ");
        Serial.println(client.getLastErrorMessage());
        return false;
    }

    Serial.println("InfluxDB connected");
    return true;
}

bool dbSendFloorTemp(float tempC, const char* ID)
{
    if (WiFi.status() != WL_CONNECTED)
        return false;

    Point p("vloer");
    p.addTag("ID", ID);
    p.addField("temp", tempC);

    if (!client.writePoint(p))
    {
        Serial.print("Floor send failed: ");
        Serial.println(client.getLastErrorMessage());
        return false;
    }

    return true;
}

bool dbSendPaalDht(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID)
{
    if (WiFi.status() != WL_CONNECTED)
        return false;

    Point p("paal");
    p.addTag("ID", ID);

    p.addField("T10", t10);
    p.addField("H10", h10);

    p.addField("T15", t15);
    p.addField("H15", h15);

    p.addField("T20", t20);
    p.addField("H20", h20);

    if (!client.writePoint(p))
    {
        Serial.print("Paal send failed: ");
        Serial.println(client.getLastErrorMessage());
        return false;
    }

    return true;
}