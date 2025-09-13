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
    Trajectory();
    void generate(TrajectoryData& data, double Ts, double lmda, double stepLength, double stepHeight, double xbound, double ybound);

private:

};

#endif