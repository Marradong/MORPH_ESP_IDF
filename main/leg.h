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

    Leg(ServoDriver& servodriver, int servo_phi_2, int servo_phi_5, bool isFront);
    void driveFullStep(double stepLength, double stepHeight);
    void driveNextStep(double stepLength, double stepHeight);
    void Home();
    void Reverse();
    void Forward();

private:
    // Servo
    ServoDriver& servodriver;
    int servo_phi_2;
    int servo_phi_5;
    bool isFront;
    bool isReverse;
    void driveLeg(double phi_2, double phi_5);
    
    // Trajectory
    int stepindex;
    void generateFullStep(TrajectoryData& data, double stepLength, double stepHeight);
    void generateNextStep(KinematicsData& data, double stepLength, double stepHeight, int idx);

    // Kinematics
    void ik(KinematicsData& data, double x, double y);
    void fk(KinematicsData& data, double phi_2, double phi_5);
    double mod(double a, double b);
};

#endif