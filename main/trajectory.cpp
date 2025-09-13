#include "trajectory.h"

Kinematics kinematics;

Trajectory::Trajectory() {
}

void Trajectory::generate(TrajectoryData& data, double Ts, double lmda, double stepLength, double stepHeight, double xbound, double ybound) {
    data.size = RESOLUTION * 2;

    double dt = (lmda * Ts) / (RESOLUTION - 1);
    double dx = stepLength / (RESOLUTION - 1);

    for (int i = 0; i < RESOLUTION; i++) {
        double t = i * dt;
        double sigma = (RAD_360 * t) / (lmda * Ts);

        kinematics.ik(data.kinematics[i], 
            ((stepLength * (sigma - sin(sigma)) / (RAD_360))) + xbound , 
            -((stepHeight * (1 - cos(sigma)) / 2)) + ybound
        );

        kinematics.ik(data.kinematics[i+RESOLUTION], 
            -xbound - i * dx, 
            ybound
        );
    }
}
