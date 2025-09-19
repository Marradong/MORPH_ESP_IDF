#include <Wire.h>
#include "batterymonitor.h"
#include "controller.h"
#include "imu.h"
#include "leg.h"
#include "servodriver.h"
#include "wifiserver.h"

BLEController blecontroller;
BatteryMonitor batterymonitor;
IMU imu;
ServoDriver servodriver;
WIFIServer wifiserver;

uint8_t STATE = STOPPED;

Leg legFL(servodriver, SERVO_FLF, SERVO_FLB, true, LAMBDA*RESOLUTION, STEP_HEIGHT);
Leg legFR(servodriver, SERVO_FRF, SERVO_FRB, true, 3*LAMBDA*RESOLUTION, STEP_HEIGHT);
Leg legBL(servodriver, SERVO_BLF, SERVO_BLB, false, 0, STEP_HEIGHT);
Leg legBR(servodriver, SERVO_BRF, SERVO_BRB, false, 2*LAMBDA*RESOLUTION, STEP_HEIGHT);

BLEController::BLEControllerData ctrlData;
IMU::IMUData imuData;
BatteryMonitor::BatteryData batteryData;

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
}

void reverse() {
  legFL.Reverse();
  legFR.Reverse();
  legBL.Reverse();
  legBR.Reverse();
}

void left() {
  legFL.Turn(STEP_SHORT);
  legFR.Turn(STEP_LONG);
  legBL.Turn(STEP_SHORT);
  legBR.Turn(STEP_LONG);
}

void right() {
  legFL.Turn(STEP_LONG);
  legFR.Turn(STEP_SHORT);
  legBL.Turn(STEP_LONG);
  legBR.Turn(STEP_SHORT);
}

void up(){
  legFL.Up();
  legFR.Up();
  legBL.Up();
  legBR.Up();
}

void down(){
  legFL.Down();
  legFR.Down();
  legBL.Down();
  legBR.Down();
}

void updateState() {
  if (STATE != HOME && ctrlData.home) {
    STATE = HOME;
    Console.println("HOME");
  } else if (STATE != FORWARD && ctrlData.forward) {
    STATE = FORWARD;
    Console.println("FORWARD");
  } else if (STATE != REVERSE && ctrlData.backward) {
    STATE = REVERSE;
    Console.println("REVERSE");
  } else if (STATE != LEFT && ctrlData.left) {
    STATE = LEFT;
    Console.println("LEFT");
  } else if (STATE != RIGHT && ctrlData.right) {
    STATE = RIGHT;
    Console.println("RIGHT");
  } else if (STATE != UP && ctrlData.up) {
    STATE = UP;
    Console.println("UP");
  } else if (STATE != DOWN && ctrlData.down) {
    STATE = DOWN;
    Console.println("DOWN");
  } else if (STATE != STOPPED && ctrlData.stopped) {
    STATE = STOPPED;
    Console.println("STOPPED");
  } else if (STATE != RESTART && ctrlData.restart) {
    STATE = RESTART;
    Console.println("RESTART");
  }
}


void setup() {
  Wire.begin();
  delay(10);
  
  // batterymonitor.begin();
  delay(10);
  
  // imu.begin();
  delay(10);
  
  servodriver.begin();
  delay(10);
  
  blecontroller.begin();
  delay(10);

  wifiserver.begin();
  delay(100);
}

void loop() {
  blecontroller.getData(ctrlData);

  batterymonitor.getData(batteryData);

  imu.getData(imuData);

  wifiserver.handleClient(ctrlData, imuData, batteryData);

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
    case UP:
      up();
      break;
    case DOWN:
      down();
      break;
    case STOPPED:
      break;
    case RESTART:
      ESP.restart();
      break;
  }

  delay(10);
}
