#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiVectraID.h>
#include <PubSubVectraID.h>
#include <SensorVectraID.h>

const char* clientID = "vectra1";
const char* topic = "vectra/id";

WiFiVectraID wifiVectra;
WiFiClient espClient;
PubSubVectraID mqtt(espClient);
SensorVectraID sensor(5, DHT22);

void setup() {
  Serial.begin(115200);
//   wifiVectra.deleteWiFiConfigFile();
  wifiVectra.begin("VECTRAID", "12345678");
  sensor.begin();
  mqtt.connect(clientID);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(12) == LOW) {
    wifiVectra.deleteWiFiConfigFile();
  }

  if (!mqtt.isConnected()) {
    mqtt.connect(clientID);
  }
  mqtt.loop();

  float temp = sensor.readTemperature();
  float hum = sensor.readHumidity();
  float lux = sensor.readLightLevel();

  StaticJsonDocument<128> doc;
  doc["id"] = clientID;
  doc["temp"] = temp;
  doc["hum"] = hum;
  doc["lux"] = lux;
  doc["room"] = wifiVectra.getRoom();

  char payload[128];
  serializeJson(doc, payload);

  mqtt.publish(topic, payload);

  Serial.println(payload);

  delay(5000);
}
