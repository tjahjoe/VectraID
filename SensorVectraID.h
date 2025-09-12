#ifndef SENSOR_VECTRAID_H
#define SENSOR_VECTRAID_H

#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>

class SensorVectraID {
public:
    SensorVectraID (uint8_t dhtPin, uint8_t dhtType);

    void begin();              
    float readTemperature();  
    float readHumidity();    
    float readLightLevel();    

private:
    DHT dht;
    BH1750 lightMeter;
    bool bh1750Ready = false;
};

#endif
