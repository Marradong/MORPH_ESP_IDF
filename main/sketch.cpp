#include <Arduino.h>
#include <Wire.h>
#include "batterymonitor.h"
#include "imu.h"
#include "servodriver.h"
#include "kinematics.h"
#include "trajectory.h"
#include "controller.h"

BLEController blecontroller;
BatteryMonitor batterymonitor;
IMU imu;
ServoDriver servodriver;
Trajectory trajectory;

Trajectory::TrajectoryData data;

// Arduino setup function. Runs in CPU 1
void setup() {
    blecontroller.begin();
    Wire.begin(); // join i2c bus with SDA and SCL pins
    delay(10);

    // batterymonitor.begin();

    //imu.begin();

    servodriver.begin();    
    delay(100);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    blecontroller.process();

    // batterymonitor.printData();
    // Serial.println();
    // delay(100);

    // imu.printData();
    // Serial.println();
    // delay(100);
    
    // trajectory.generate(data, 1, 0.5, 100.0, 50.0, -50.0, 100.0);
  
    // uint8_t servo1 = SERVO_FLF;
    // uint8_t servo2 = SERVO_FLB;
    // uint8_t servo3 = SERVO_BLF;
    // uint8_t servo4 = SERVO_BLB;
    // uint8_t servo5 = SERVO_FRF;
    // uint8_t servo6 = SERVO_FRB;
    // uint8_t servo7 = SERVO_BRF;
    // uint8_t servo8 = SERVO_BRB;

    // int j = 0;

    // for (int i = 0; i < data.size; i++) {

    //     if (data.kinematics[i].phi_2 < 0 || data.kinematics[i].phi_5 < 0 || data.kinematics[i].phi_2 > 180 || data.kinematics[i].phi_5 > 180) {
    //     Serial.println("Skipping point due to IK error");
    //     continue;
    //     }

    //     j = i+RESOLUTION < data.size ? i+RESOLUTION : i-RESOLUTION < 0 ? 0 : i-RESOLUTION;

    //     servodriver.driveServo(servo1, data.kinematics[i].phi_2);
    //     servodriver.driveServo(servo2, data.kinematics[i].phi_5);
    //     servodriver.driveServo(servo3, data.kinematics[j].phi_2);
    //     servodriver.driveServo(servo4, data.kinematics[j].phi_5);
    //     servodriver.driveServo(servo5, data.kinematics[j].phi_2);
    //     servodriver.driveServo(servo6, data.kinematics[j].phi_5);
    //     servodriver.driveServo(servo7, data.kinematics[i].phi_2);
    //     servodriver.driveServo(servo8, data.kinematics[i].phi_5);
    //     delay(15);
    // }

    // for (int i = 0; i < data.size; i++) {

    //     if (data.kinematics[i].phi_2 < 0 || data.kinematics[i].phi_5 < 0 || data.kinematics[i].phi_2 > 180 || data.kinematics[i].phi_5 > 180) {
    //     Serial.println("Skipping point due to IK error");
    //     continue;
    //     }

    //     j = i+RESOLUTION < data.size ? i+RESOLUTION : i-RESOLUTION < 0 ? 0 : i-RESOLUTION;

    //     servodriver.driveServo(servo1, data.kinematics[i].phi_2);
    //     servodriver.driveServo(servo2, data.kinematics[i].phi_5);
    //     servodriver.driveServo(servo3, data.kinematics[j].phi_2);
    //     servodriver.driveServo(servo4, data.kinematics[j].phi_5);
    //     servodriver.driveServo(servo5, data.kinematics[j].phi_2);
    //     servodriver.driveServo(servo6, data.kinematics[j].phi_5);
    //     servodriver.driveServo(servo7, data.kinematics[i].phi_2);
    //     servodriver.driveServo(servo8, data.kinematics[i].phi_5);
    //     delay(15);
    // }
  delay(150);
}
