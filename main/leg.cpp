#include "leg.h"

Leg::Leg(ServoDriver& servodriver, int servo_phi_2, int servo_phi_5, bool isFront, int gaitOffset, int stepHeight) : 
    servodriver(servodriver), 
    servo_phi_2(servo_phi_2), 
    servo_phi_5(servo_phi_5), 
    isFront(isFront), 
    gaitOffset(gaitOffset),
    stepOffset(WORKSPACE_Y_MIN),
    stepHeight(stepHeight),
    isReverse(false),
    stepindex(0 + gaitOffset) {
}

void Leg::Home() {
    KinematicsData data;
    stepindex = 0 + gaitOffset;
    driveNextStep(100);
    stepindex = 0 + gaitOffset;
}

void Leg::driveLeg(double phi_2, double phi_5) {
    servodriver.driveServo(servo_phi_2, phi_2);
    servodriver.driveServo(servo_phi_5, phi_5);
}

void Leg::driveFullStep(double stepLength) {
    TrajectoryData data;
    generateFullStep(data, stepLength);
    for (int i = 0; i < data.size; i++) {
        driveLeg(data.kinematics[i].phi_2, data.kinematics[i].phi_5);
        delay(15);
    }
    stepindex = 0 + gaitOffset;
}

void Leg::driveNextStep(double stepLength) {
    KinematicsData data;
    generateNextStep(data, stepLength, stepindex);
    driveLeg(data.phi_2, data.phi_5);
    stepindex = isReverse ? (stepindex - 1) : (stepindex + 1);
    if (stepindex >= RESOLUTION) stepindex = 0;
    if (stepindex < 0) stepindex = RESOLUTION - 1;
}

void Leg::generateFullStep(TrajectoryData& data, double stepLength) {
    data.size = RESOLUTION;

    for (int i = 0; i < RESOLUTION; i++) {
        generateNextStep(data.kinematics[i], stepLength, i);
    }
}

void Leg::generateNextStep(KinematicsData& data, double stepLength, int idx) {
    if (idx < LAMBDA * RESOLUTION){
        double sigma = (RAD_360 * idx) / ((LAMBDA * RESOLUTION) - 1);
        ik(data, 
            ((stepLength * (sigma - sin(sigma)) / (RAD_360))) + (-stepLength/2) , 
            -((stepHeight * (1 - cos(sigma)) / 2)) + (stepOffset + stepHeight)
        );
    }
    else if (idx < RESOLUTION){
        double dx = stepLength / (((1-LAMBDA) * RESOLUTION) - 1);
        ik(data, 
            (stepLength/2) - (idx-(LAMBDA * RESOLUTION)) * dx, 
            stepOffset + stepHeight
        );
    }
}

void Leg::ik(KinematicsData& data, double x, double y) {
    data.x = x;
    data.y = y;

    if(x < WORKSPACE_X_MIN || x > WORKSPACE_X_MAX || y < WORKSPACE_Y_MIN || y > WORKSPACE_Y_MAX) {
        Console.printf("IK out of bounds: x=%.2f, y=%.2f\n", x, y);
        data.phi_2 = -1;
        data.phi_5 = -1;
        return;
    }

    // Calculate coefficients
    double A_2 = -L_2_5 * (2*x + L_1);
    double A_5 = -L_2_5 * (2*x - L_1);
    double B_2_5 = -2 * L_2_5 * y;
    double C_2 = x*x + y*y + L_1*L_1/ 4 + L_2_5*L_2_5 - L_3_4*L_3_4 + L_1*x;
    double C_5 = C_2 - 2*L_1*x;

    // Calculate angles
    double phi_2_sqrt = sqrt(A_2*A_2 + B_2_5*B_2_5 - C_2*C_2);
    double phi_5_sqrt = sqrt(A_5*A_5 + B_2_5*B_2_5 - C_5*C_5);

    double phi_2_n = mod(2.0 * atan2((B_2_5 - phi_2_sqrt), (A_2 - C_2)), RAD_360);
    double phi_2_p = mod(2.0 * atan2((B_2_5 + phi_2_sqrt), (A_2 - C_2)), RAD_360);

    double phi_5_n = mod(2.0 * atan2((B_2_5 - phi_5_sqrt), (A_5 - C_5)), RAD_360);
    double phi_5_p = mod(2.0 * atan2((B_2_5 + phi_5_sqrt), (A_5 - C_5)), RAD_360);

    // Select correct angle
    data.phi_2 = (phi_2_n >= RAD_90 && phi_2_n <= RAD_270) ? phi_2_n : phi_2_p;
    data.phi_5 = ((phi_5_n >= 0.0 && phi_5_n <= RAD_90) || (phi_5_n >= RAD_270 && phi_5_n <= RAD_360)) ? phi_5_n : phi_5_p;

    data.phi_2 = (data.phi_2 - RAD_90)*RAD_TO_DEG;
    data.phi_5 = (data.phi_5 >= RAD_270 ? RAD_450 - data.phi_5 : RAD_90 - data.phi_5)*RAD_TO_DEG;

    return;
}

void Leg::fk(KinematicsData& data, double phi_2, double phi_5) {
    phi_2 = phi_2*DEG_TO_RAD;
    phi_2 += RAD_90;
    phi_5 = phi_5*DEG_TO_RAD;
    phi_5 = phi_5 >= RAD_270 ? RAD_450 - phi_5 : RAD_90 - phi_5;

    double L_s_x = L_1 + L_2_5*cos(phi_5) - L_2_5*cos(phi_2);
    double L_s_y = L_2_5*cos(phi_5) - L_2_5*cos(phi_2);
    double L_s = sqrt(L_s_x*L_s_x + L_s_y*L_s_y);
    double phi_s = atan2(L_s_y, L_s_x)+PI;

    double phi = acos(-L_s*L_s / (2*L_s*L_3_4));

    double phi_3 = phi_s - phi;
    double phi_4 = phi_s + phi;

    data.x = -L_1/2 + L_2_5*cos(phi_2) + L_3_4*cos(phi_3);
    data.y = L_2_5*sin(phi_2) + L_3_4*sin(phi_3);

    return;
}

double Leg::mod(double a, double b) {
    return a - b * floor(a / b);
}

void Leg::Reverse() {
    isReverse = true;
    driveNextStep(STEP_LONG);
}

void Leg::Forward() {
    isReverse = false;
    driveNextStep(STEP_LONG);
}

void Leg::Turn(double stepLength) {
    isReverse = false;
    driveNextStep(stepLength);
}


void Leg::StepHeight(int height) {
    stepHeight = height;
}

void Leg::Up() {
    if (stepOffset + 1 + stepHeight > WORKSPACE_Y_MAX) {
        stepOffset = WORKSPACE_Y_MAX - stepHeight;
    } else {
        stepOffset++;
    }

    stepindex = isReverse ? (stepindex + 1) : (stepindex - 1);
    if (stepindex >= RESOLUTION) stepindex = 0;
    if (stepindex < 0) stepindex = RESOLUTION - 1;

    driveNextStep(STEP_LONG);
}

void Leg::Down() {
    if (stepOffset - 1 < WORKSPACE_Y_MIN) {
        stepOffset = WORKSPACE_Y_MIN;
    } else {
        stepOffset--;
    }

    stepindex = isReverse ? (stepindex + 1) : (stepindex - 1);
    if (stepindex >= RESOLUTION) stepindex = 0;
    if (stepindex < 0) stepindex = RESOLUTION - 1;

    driveNextStep(STEP_LONG);
}