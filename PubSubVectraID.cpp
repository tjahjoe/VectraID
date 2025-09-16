#include "PubSubVectraID.h"

PubSubVectraID::PubSubVectraID(Client& netClient) : client(netClient) {
    client.setServer(MQTT_BROKER, MQTT_PORT);
}

void PubSubVectraID::connect(const char *clientID) {
    while (!client.connected()) {
        String client_id = clientID;
        Serial.printf("Connecting as %s ...\n", client_id.c_str());

        // if (client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
        if (client.connect(client_id.c_str())) {
            Serial.println("Connected to EMQX MQTT broker");
        } else {
            Serial.print("Failed, state: ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

bool PubSubVectraID::isConnected() {
    return client.connected();
}

void PubSubVectraID::loop() {
    client.loop();
}

void PubSubVectraID::publish(const char* topic, const char* payload) {
    if (client.connected()) {
        if (client.publish(topic, payload)) {
            Serial.printf("Published to %s: %s\n", topic, payload);
        } else {
            Serial.printf("Failed to publish to %s\n", topic);
        }
    } else {
        Serial.println("MQTT not connected, cannot publish");
    }
}

PubSubClient& PubSubVectraID::getClient() {
    return client;
}
