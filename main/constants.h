#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

#define INA228_SHUNT_RESISTANCE 0.015
#define INA228_MAX_CURRENT 10.0

#define IMU_ACCELEROMETER_DIVISOR 255
#define IMU_GYROSCOPE_DIVISOR 255

#define RAD_90 (PI/2)
#define RAD_270 (3*PI/2)
#define RAD_360 (2*PI)
#define RAD_450 (5*PI/2)

#define L_1 50.0
#define L_2_5 48.5
#define L_3_4 92.8


#define OSCILLATOR_FREQUENCY 25000000
#define SERVO_FREQUENCY 50
#define SERVO_NUMBER 8
#define SERVO_MAX_ANGLE 180.0
#define SERVO_MIN_ANGLE 0.0

#define SERVO_FLB 0 // 108, 544
#define SERVO_FLF 1 // 108, 548
#define SERVO_BLF 2 // 108, 544
#define SERVO_BLB 3 // 108, 548
#define SERVO_BRF 4 // 108, 544
#define SERVO_BRB 5 // 108, 548
#define SERVO_FRF 6 // 108, 544
#define SERVO_FRB 7 // 108, 548

#define RESOLUTION 100

#define WORKSPACE_X_MIN -50
#define WORKSPACE_X_MAX 50
#define WORKSPACE_Y_MIN 50
#define WORKSPACE_Y_MAX 100

#define LAMBDA 0.25

#define HOME 0
#define FORWARD 1
#define REVERSE 2
#define LEFT 3
#define RIGHT 4
#define STOPPED 5

#endif