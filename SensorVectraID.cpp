#include "SensorVectraID.h"

SensorVectraID::SensorVectraID(uint8_t dhtPin, uint8_t dhtType) : dht(dhtPin, dhtType) {}

void SensorVectraID::begin() {
    dht.begin();

    // Wire.begin();
    Wire.begin(21, 22);
    // if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    //     bh1750Ready = true;
    // } else {
    //     bh1750Ready = false;
    // }
    lightMeter.begin();
}

float SensorVectraID::readTemperature() {
    return dht.readTemperature();
}

float SensorVectraID::readHumidity() {
    return dht.readHumidity();
}

float SensorVectraID::readLightLevel() {
    // if (bh1750Ready) {
    //     return lightMeter.readLightLevel();
    // }
    // return -1.0;
    return lightMeter.readLightLevel();
}
