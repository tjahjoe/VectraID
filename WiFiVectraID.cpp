#include "WiFiVectraID.h"

WiFiVectraID::WiFiVectraID()
{
    initLittleFS();
}

void WiFiVectraID::begin(const char *apName, const char *apPassword)
{
    String ssid, password;
    bool credentialsLoaded = loadWiFiCredentials(ssid, password);

    WiFiManager wm;
    wm.setSaveConfigCallback(saveWiFiManagerParamsCallback);

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
            if (!wm.autoConnect(apName, apPassword))
            {
                ESP.restart();
            }
        }
    }
    else
    {
        if (!wm.autoConnect(apName, apPassword))
        {
            ESP.restart();
        }
    }
}

void WiFiVectraID::initLittleFS()
{
    if (!LittleFS.begin(true))
    {
        Serial.println(F("ERROR: LittleFS Mount Failed"));
    }
}

void WiFiVectraID::saveWiFiCredentials(const String &ssid, const String &password)
{
    File file = LittleFS.open(CONFIG_FILE, "w");
    if (!file)
        return;
    file.println(ssid);
    file.println(password);
    file.close();
}

bool WiFiVectraID::loadWiFiCredentials(String &ssid, String &password)
{
    File file = LittleFS.open(CONFIG_FILE, "r");
    if (!file)
        return false;
    ssid = file.readStringUntil('\n');
    ssid.trim();
    password = file.readStringUntil('\n');
    password.trim();
    file.close();
    return (ssid.length() > 0);
}

void WiFiVectraID::saveWiFiManagerParamsCallback()
{
    saveWiFiCredentials(WiFi.SSID(), WiFi.psk());
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
