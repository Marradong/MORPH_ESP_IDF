#ifndef LEG_H
#define LEG_H

#include <Arduino.h>
#include <ArduinoConsole.h>
#include "servodriver.h"
#include "constants.h"

class Leg {
public:
    struct KinematicsData{
        double x;
        double y;
        double phi_2;
        double phi_5;
    };

    struct TrajectoryData{
        KinematicsData kinematics[RESOLUTION*2];
        int size;
    };

    Leg(ServoDriver& servodriver, int servo_phi_2, int servo_phi_5, bool isFront, int gaitOffset, int stepHeight);
    void driveFullStep(double stepLength);
    void driveNextStep(double stepLength);
    void Home();
    void Reverse();
    void Forward();
    void Turn(double stepLength);
    void StepHeight(int stepHeight);
    void Up();
    void Down();

private:
    // Servo
    ServoDriver& servodriver;
    int servo_phi_2;
    int servo_phi_5;
    bool isFront;
    bool isReverse;
    int gaitOffset;
    int stepOffset;
    int stepHeight;
    void driveLeg(double phi_2, double phi_5);
    
    // Trajectory
    int stepindex;
    void generateFullStep(TrajectoryData& data, double stepLength);
    void generateNextStep(KinematicsData& data, double stepLength, int idx);

    // Kinematics
    void ik(KinematicsData& data, double x, double y);
    void fk(KinematicsData& data, double phi_2, double phi_5);
    double mod(double a, double b);
};

#endif