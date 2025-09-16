#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <ArduinoConsole.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "constants.h"

class IMU {
public:
    struct IMUData {
        sensors_event_t accelerometer;
        sensors_event_t gyroscope;
        sensors_event_t magnetometer;
        sensors_event_t temperature;
    };

    IMU();
    void begin();
    void printData();
    void printData(IMUData& data);
    IMUData getData();

private:
    Adafruit_ICM20948 _imu;
};


#endif