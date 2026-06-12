/*
* bestand: DataSend.cpp
* auteurs: Stan Dam, Amber Laçi, Jelle Joustra
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
bool connectWiFi(const char* ssid, const char* pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    //WiFi.setTxPower(WIFI_POWER_8_5dBm);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 20000)
    {
        if (start % 250){
        digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED)); 
    }
        }//knipperen mss handiger in main maar komt nu hier net iets beter uit

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
bool dbBegin(const char* dbURL, const char* dbName, const char* dbUser, const char* dbPass)
{
    //if (!connectWiFi()) return false;     //niet super zeker of deze lijn nodig is

    client.setConnectionParamsV1(
        dbURL,
        dbName,
        dbUser,
        dbPass
    );

    if (!client.validateConnection()) return false;
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
    if (!client.validateConnection()) return false;

    Point p("vloer");
    p.addTag("ID", ID);
    p.addField("T", T);

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
bool dbSendPaalDHT(float t10, float h10, float t15, float h15, float t20, float h20, const char* ID)
{
    if (!client.validateConnection()) return false;
        
    Point p("lucht");
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