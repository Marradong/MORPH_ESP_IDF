#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Arduino.h>
#include <math.h>
#include "constants.h"

class Kinematics {
public:
    struct KinematicsData{
        double x;
        double y;
        double phi_2;
        double phi_5;
    };

    Kinematics();
    void ik(KinematicsData& data, double x, double y);
    void fk(KinematicsData& data, double phi_2, double phi_5);

private:
    double mod(double a, double b);
};

#endif