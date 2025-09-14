#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <Arduino.h>
#include "kinematics.h"
#include "constants.h"

class Trajectory {
public:
    struct TrajectoryData{
        Kinematics::KinematicsData kinematics[RESOLUTION*2];
        int size;
    };
    Trajectory(Kinematics& kinematics);
    void fullStep(TrajectoryData& data, double stepLength, double stepHeight);
    void nextStep(Kinematics::KinematicsData& data, double stepLength, double stepHeight, int idx);

private:
    Kinematics& kinematics;
};

#endif