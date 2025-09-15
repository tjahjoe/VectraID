#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiVectraID.h>
#include <PubSubVectraID.h>
#include <SensorVectraID.h>

WiFiVectraID wifiVectra;
WiFiClient espClient;
PubSubVectraID mqtt(espClient);
SensorVectraID sensor(5, DHT22); 

void setup() {
    Serial.begin(115200);
    // wifiVectra.deleteWiFiConfigFile();
    wifiVectra.begin("VECTRAID", "12345678");
    sensor.begin();
    mqtt.connect();
}

void loop() {
    if (!mqtt.isConnected()) {
        mqtt.connect();
    }
    mqtt.loop();

    float temp = sensor.readTemperature();
    float hum  = sensor.readHumidity();
    float lux  = sensor.readLightLevel();

    StaticJsonDocument<128> doc;
    doc["temp"] = temp;
    doc["hum"]  = hum;
    doc["lux"]  = lux;
    doc["room"] = wifiVectra.getRoom();

    char payload[128];
    serializeJson(doc, payload);

    mqtt.publish("vectra/id", payload);

    Serial.println(payload);

    delay(5000);
}
