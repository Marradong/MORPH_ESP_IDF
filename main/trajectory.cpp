#include "trajectory.h"

Trajectory::Trajectory(Kinematics& kinematics) : kinematics(kinematics) {
}

void Trajectory::fullStep(TrajectoryData& data, double stepLength, double stepHeight) {
    data.size = RESOLUTION * 2;

    for (int i = 0; i < RESOLUTION; i++) {
        nextStep(data.kinematics[i], stepLength, stepHeight, i);
        nextStep(data.kinematics[i+RESOLUTION], stepLength, stepHeight, i+RESOLUTION);
    }
}

void Trajectory::nextStep(Kinematics::KinematicsData& data, double stepLength, double stepHeight, int idx) {
    if (idx < RESOLUTION){
        double sigma = (RAD_360 * idx * DT) / (LAMBDA * TS);
        kinematics.ik(data, 
            ((stepLength * (sigma - sin(sigma)) / (RAD_360))) + (-stepLength/2) , 
            -((stepHeight * (1 - cos(sigma)) / 2)) + (WORKSPACE_Y_MIN + stepHeight)
        );
    }
    else if (idx < RESOLUTION*2){
        double dx = stepLength / (RESOLUTION - 1);
        kinematics.ik(data, 
            (stepLength/2) - idx * dx, 
            WORKSPACE_Y_MIN + stepHeight
        );
    }
}
