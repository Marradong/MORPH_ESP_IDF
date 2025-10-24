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

Leg legFL(servodriver, SERVO_FLF, SERVO_FLB, true, LAMBDA*RESOLUTION);
Leg legFR(servodriver, SERVO_FRF, SERVO_FRB, true, 3*LAMBDA*RESOLUTION);
Leg legBL(servodriver, SERVO_BLF, SERVO_BLB, false, 0);
Leg legBR(servodriver, SERVO_BRF, SERVO_BRB, false, 2*LAMBDA*RESOLUTION);

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

void legUp(){
  legFL.LegUp();
  legFR.LegUp();
  legBL.LegUp();
  legBR.LegUp();
}

void legDown(){
  legFL.LegDown();
  legFR.LegDown();
  legBL.LegDown();
  legBR.LegDown();
}

void stepUp(){
  legFL.StepUp();
  legFR.StepUp();
  legBL.StepUp();
  legBR.StepUp();
}

void stepDown(){
  legFL.StepDown();
  legFR.StepDown();
  legBL.StepDown();
  legBR.StepDown();
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
  } else if (STATE != LEG_UP && ctrlData.legUp) {
    STATE = LEG_UP;
    Console.println("LEG_UP");
  } else if (STATE != LEG_DOWN && ctrlData.legDown) {
    STATE = LEG_DOWN;
    Console.println("LEG_DOWN");
  } else if (STATE != STEP_UP && ctrlData.stepUp) {
    STATE = STEP_UP;
    Console.println("STEP_UP");
  } else if (STATE != STEP_DOWN && ctrlData.stepDown) {
    STATE = STEP_DOWN;
    Console.println("STEP_DOWN");
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
  
  batterymonitor.begin();
  delay(10);
  
  imu.begin();
  delay(10);
  
  servodriver.begin();
  delay(10);
  
  blecontroller.begin();
  delay(10);
}

void loop() {
  blecontroller.getData(ctrlData);

  batterymonitor.getData(batteryData);

  imu.getData(imuData);

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
    case LEG_UP:
      legUp();
      break;
    case LEG_DOWN:
      legDown();
      break;
    case STEP_UP:
      stepUp();
      break;
    case STEP_DOWN:
      stepDown();
      break;
    case STOPPED:
      break;
    case RESTART:
      ESP.restart();
      break;
  }

  delay(10);
}
