#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>
#include <Adafruit_INA228.h>
#include "constants.h"

class BatteryMonitor {
public:
    struct BatteryData {
        float current;
        float voltage;
        float shuntvoltage;
        float power;
        float energy;
        float charge;
        float temperature;
    };

    BatteryMonitor();
    void begin();
    void printData();
    void printData(BatteryData& data);
    BatteryData getData();

private:
    Adafruit_INA228 _batterymonitor;
};

#endif