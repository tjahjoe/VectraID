#ifndef PUBSUB_VECTRAID_H
#define PUBSUB_VECTRAID_H

#include <WiFi.h>
#include <PubSubClient.h>

class PubSubVectraID {
public:
    PubSubVectraID(Client& netClient);
    void connect(const char *clientID);
    bool isConnected();
    void loop();
    void publish(const char* topic, const char* payload);  
    PubSubClient& getClient();

private:
    PubSubClient client;
    static constexpr const char* MQTT_BROKER   = "103.245.39.160";
    static constexpr uint16_t    MQTT_PORT     = 1883;
    // static constexpr const char* MQTT_USERNAME = "Vectra";
    // static constexpr const char* MQTT_PASSWORD = "12345";
};

#endif
