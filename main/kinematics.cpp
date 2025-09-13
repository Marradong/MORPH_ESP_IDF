#include "kinematics.h"

Kinematics::Kinematics() {
    // Constructor implementation
}

void Kinematics::ik(KinematicsData& data, double x, double y) {
    data.x = x;
    data.y = y;

    if(x < WORKSPACE_X_MIN || x > WORKSPACE_X_MAX || y < WORKSPACE_Y_MIN || y > WORKSPACE_Y_MAX) {
        // Serial.println("Position out of workspace");
        data.phi_2 = -1;
        data.phi_5 = -1;
        return;
    }

    // Serial.print("Calculating IK for ("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(")");

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

    // Serial.print("IK result (rad): ("); Serial.print(data.phi_2); Serial.print(", "); Serial.print(data.phi_5); Serial.println(")");

    data.phi_2 = (data.phi_2 - RAD_90)*RAD_TO_DEG;
    data.phi_5 = (data.phi_5 >= RAD_270 ? RAD_450 - data.phi_5 : RAD_90 - data.phi_5)*RAD_TO_DEG;

    // Serial.print("IK result (deg): ("); Serial.print(data.phi_2); Serial.print(", "); Serial.print(data.phi_5); Serial.println(")");

    return;
}

void Kinematics::fk(KinematicsData& data, double phi_2, double phi_5) {
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

double Kinematics::mod(double a, double b) {
    return a - b * floor(a / b);
}
