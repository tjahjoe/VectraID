#ifndef WIFI_VECTRAID_H
#define WIFI_VECTRAID_H

#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <WiFiManager.h>

class WiFiVectraID
{
public:
    WiFiVectraID();
    void begin(const char* apName, const char* apPassword);
    void deleteWiFiConfigFile();

private:
    void initLittleFS();
    static void saveWiFiManagerParamsCallback();
    static void saveWiFiCredentials(const String &ssid, const String &password);
    static bool loadWiFiCredentials(String &ssid, String &password);

    static constexpr const char *CONFIG_FILE = "/wifi_config.txt";
};

#endif
