#include <Arduino.h>
#include <Wire.h>
#include "batterymonitor.h"
#include "controller.h"
#include "imu.h"
#include "leg.h"
#include "servodriver.h"

BLEController blecontroller;
BatteryMonitor batterymonitor;
IMU imu;
ServoDriver servodriver;

uint8_t STATE = STOPPED;

Leg legFL(servodriver, SERVO_FLF, SERVO_FLB, true);
Leg legFR(servodriver, SERVO_FRF, SERVO_FRB, true);
Leg legBL(servodriver, SERVO_BLF, SERVO_BLB, false);
Leg legBR(servodriver, SERVO_BRF, SERVO_BRB, false);

void home() {
  legFL.Home();
  legFR.Home();
  legBL.Home();
  legBR.Home();
  delay(500);
}

void forward() {
  legFL.Forward();
  legFR.Forward();
  legBL.Forward();
  legBR.Forward();

  legFL.driveNextStep(100, 50);
  legBR.driveNextStep(100, 50);
  legFR.driveNextStep(100, 50);
  legBL.driveNextStep(100, 50);
}

void reverse() {
  legFL.Reverse();
  legFR.Reverse();
  legBL.Reverse();
  legBR.Reverse();

  legFL.driveNextStep(100, 50);
  legBR.driveNextStep(100, 50);
  legFR.driveNextStep(100, 50);
  legBL.driveNextStep(100, 50);
}

void left() {
  legFL.Forward();
  legFR.Forward();
  legBL.Forward();
  legBR.Forward();

  legFL.driveNextStep(50, 50);
  legBR.driveNextStep(100, 50);
  legFR.driveNextStep(100, 50);
  legBL.driveNextStep(50, 50);
}

void right() {
  legFL.Forward();
  legFR.Forward();
  legBL.Forward();
  legBR.Forward();

  legFL.driveNextStep(100, 50);
  legBR.driveNextStep(50, 50);
  legFR.driveNextStep(50, 50);
  legBL.driveNextStep(100, 50);
}

void updateState() {
  if (STATE != HOME && blecontroller.home()) {
    STATE = HOME;
    Console.println("HOME");
  } else if (STATE != FORWARD && blecontroller.up()) {
    STATE = FORWARD;
    Console.println("FORWARD");
  } else if (STATE != REVERSE && blecontroller.down()) {
    STATE = REVERSE;
    Console.println("REVERSE");
  } else if (STATE != LEFT && blecontroller.left()) {
    STATE = LEFT;
    Console.println("LEFT");
  } else if (STATE != RIGHT && blecontroller.right()) {
    STATE = RIGHT;
    Console.println("RIGHT");
  } else if (STATE != STOPPED && !blecontroller.up() && !blecontroller.down() && !blecontroller.left() && !blecontroller.right() && !blecontroller.home()) {
    STATE = STOPPED;
    Console.println("STOPPED");
  }
}


// Arduino setup function. Runs in CPU 1
void setup() {
  blecontroller.begin();
  Wire.begin();  // join i2c bus with SDA 21 and SCL 22 pins
  delay(10);

  // batterymonitor.begin();

  // imu.begin();

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

  updateState();

  switch (STATE) {
    case HOME:
      home();
      break;
    case FORWARD:
      forward();
      break;
    case REVERSE:
      reverse();
      break;
    case LEFT:
      left();
      break;
    case RIGHT:
      right();
      break;
    case STOPPED:
      break;
  }

  delay(25);
}
