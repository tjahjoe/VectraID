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
    void begin(const char *apName, const char *apPassword);
    void deleteWiFiConfigFile();
    String getRoom();

private:
    void initLittleFS();
    void saveWiFiCredentials(const String &ssid, const String &password, const String &room);
    bool loadWiFiCredentials(String &ssid, String &password, String &room);

    static constexpr const char *CONFIG_FILE = "/wifi_config.txt";
    String _room;
};

#endif
