#include "WiFiVectraID.h"

WiFiVectraID::WiFiVectraID()
{
    initLittleFS();
}

void WiFiVectraID::begin(const char *apName, const char *apPassword)
{
    String ssid, password, room;
    bool credentialsLoaded = loadWiFiCredentials(ssid, password, room);

    WiFiManager wm;

    WiFiManagerParameter custom_room("room", "Room", room.c_str(), 32);
    wm.addParameter(&custom_room);

    if (credentialsLoaded)
    {
        WiFi.begin(ssid.c_str(), password.c_str());

        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000)
        {
            delay(500);
            Serial.print(F("."));
        }
        Serial.println();

        if (WiFi.status() != WL_CONNECTED)
        {
            if (!wm.startConfigPortal(apName, apPassword))
            {
                ESP.restart();
            }
        }
    }
    else
    {
        // if (!wm.autoConnect(apName, apPassword))
        if (!wm.startConfigPortal(apName, apPassword))
        {
            ESP.restart();
        }
    }

    room = custom_room.getValue();
    _room = room;
    _room.trim();  

    saveWiFiCredentials(WiFi.SSID(), WiFi.psk(), room);
}

void WiFiVectraID::initLittleFS()
{
    if (!LittleFS.begin(true))
    {
        Serial.println(F("ERROR: LittleFS Mount Failed"));
    }
}

void WiFiVectraID::saveWiFiCredentials(const String &ssid, const String &password, const String &room)
{
    File file = LittleFS.open(CONFIG_FILE, "w");
    if (!file)
        return;

    file.println(ssid);
    file.println(password);
    file.println(room);

    file.close();
}

bool WiFiVectraID::loadWiFiCredentials(String &ssid, String &password, String &room)
{
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file)
        return false;

    ssid = file.readStringUntil('\n');
    ssid.trim();
    password = file.readStringUntil('\n');
    password.trim();
    room = file.readStringUntil('\n');
    room.trim();

    file.close();

    _room = room;

    return (ssid.length() > 0);
}

String WiFiVectraID::getRoom()
{
    return _room;
}

void WiFiVectraID::deleteWiFiConfigFile()
{
    if (LittleFS.exists(CONFIG_FILE))
    {
        LittleFS.remove(CONFIG_FILE);
        Serial.println("wifi_config.txt deleted.");
    }
    else
    {
        Serial.println("wifi_config.txt not found.");
    }
}
