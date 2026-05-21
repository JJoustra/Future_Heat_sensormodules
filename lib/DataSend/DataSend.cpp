/*
* bestand: DataSend.cpp
* auteur: Stan Dam 
* versie: 1.1
* Code bestand met de functies om gemeten waardes naar de influxdb te schrijven. 
* WiFi instellingen en database toegang dienen in DataSend.h te worden ingevoerd.
*/
#include "DataSend.h"

/**
 * @brief begint de wifi verbinding. Tijdens verbinden knippert de blauwe led.
 * Als deze na 20s nog niet is verbonden blijft de led aan. druk in dit geval op reset en controlleer de wifi instellinden in DataSend.h
 * @return simpele true/false of de verbinding is gelukt.
 */
static bool connectWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
    Serial.print("Connecting to WiFi");

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 20000)
    {
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        return false;
    }
    return true;
}
/**
 * @brief start de verbinding met de database en controleert vervolgens of voor succes.
 * @return simpele true/false of de verbinding is gelukt.
 */
bool dbBegin()
{
    if (!connectWiFi()) return false;

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

/**
 * @brief schrijf functie voor de vloermodules. Schrijft de actuele temperatuur en ID van de module naar de database.
 * @param T gemeten temperatuur in celsius.
 * @param ID identifikatie van de specifieke module. Lager getal komt overeen met een module die dichter bij de invoer ligt.
 * @return simpele true/false of de verbinding is gelukt.
 */
bool dbSendFloorTemp(float T, const char* ID)
{
    if (WiFi.status() != WL_CONNECTED) return false;

    Point p("vloer");
    p.addTag("ID", ID);
    p.addField("temp", T);

    if (!client.writePoint(p)) return false;

    return true;
}

/**
 * @brief schrijf functie voor de paal modules. Actuele temperatuur en luchtvochtigheid van 1m, 1.5m en 2m met de id van de module.
 * @param T10 gemeten temperatuur op 1m hoogte in celsius.
 * @param H10 gemeten luchtvochtigheid op 1m hoogte in %.
 * @param T15 gemeten temperatuur op 1.5m hoogte in celsius.
 * @param H15 gemeten luchtvochtigheid op 1.5m hoogte in %.
 * @param T20 gemeten temperatuur op 2m hoogte in celsius.
 * @param H20 gemeten luchtvochtigheid op 2m hoogte in %.
 * @param ID identifikatie van de specifieke module.
 */
bool dbSendPaalDht(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID)
{
    if (WiFi.status() != WL_CONNECTED) return false;
        
    Point p("paal");
    p.addTag("ID", ID);

    p.addField("T10", t10);
    p.addField("H10", h10);

    p.addField("T15", t15);
    p.addField("H15", h15);

    p.addField("T20", t20);
    p.addField("H20", h20);

    if (!client.writePoint(p)) return false;

    return true;
}