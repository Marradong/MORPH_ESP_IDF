#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H 

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include "constants.h"

class ServoDriver {
public:

    static constexpr uint16_t SERVO_MAX_PULSE[SERVO_NUMBER] = {544, 548, 548, 544, 544, 548, 544, 548};
    static constexpr uint16_t SERVO_MIN_PULSE[SERVO_NUMBER] = {108, 108, 108, 108, 108, 108, 108, 108}; 
    static constexpr uint16_t SERVO_TOP[SERVO_NUMBER] = {
        SERVO_MIN_PULSE[0], 
        SERVO_MAX_PULSE[1], 
        SERVO_MAX_PULSE[2], 
        SERVO_MIN_PULSE[3], 
        SERVO_MIN_PULSE[4], 
        SERVO_MAX_PULSE[5], 
        SERVO_MIN_PULSE[6], 
        SERVO_MAX_PULSE[7]
    };
    static constexpr uint16_t SERVO_BOTTOM[SERVO_NUMBER] = {
        SERVO_MAX_PULSE[0], 
        SERVO_MIN_PULSE[1], 
        SERVO_MIN_PULSE[2], 
        SERVO_MAX_PULSE[3], 
        SERVO_MAX_PULSE[4], 
        SERVO_MIN_PULSE[5], 
        SERVO_MAX_PULSE[6], 
        SERVO_MIN_PULSE[7]
    };

    ServoDriver();
    void begin();
    void driveServo(uint8_t servo, double angle);
    void driveServo(uint8_t servo, uint16_t pwm);
    void sweepServo(uint8_t servo);
    void driveToTop(uint8_t servo);
    void driveToBottom(uint8_t servo);

private:
    Adafruit_PWMServoDriver  _servodriver;
    long pulseFromAngle(uint8_t servo, double angle);
};

#endif