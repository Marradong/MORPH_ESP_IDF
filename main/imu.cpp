#include "imu.h"

IMU::IMU() { _imu = Adafruit_ICM20948(); }

void IMU::begin() {
    Console.println("Initialise Adafruit ICM20948");

    if (!_imu.begin_I2C()) {
        Console.println("Failed to find ICM20948 chip");
        return;
    }

    Console.println("Found ICM20948 chip");
    
    _imu.setAccelRange(ICM20948_ACCEL_RANGE_4_G);
    Console.println("Accelerometer range set to: +-4 G");

    _imu.setGyroRange(ICM20948_GYRO_RANGE_500_DPS);
    Console.println("Gyro range set to: 500 degrees/s");

    _imu.setAccelRateDivisor(IMU_ACCELEROMETER_DIVISOR);
    float accel_rate = 1125 / (1.0 + IMU_ACCELEROMETER_DIVISOR);
    Console.print("Accelerometer data rate divisor set to: "); Console.print(IMU_ACCELEROMETER_DIVISOR); Console.print("\n");
    Console.print("Accelerometer data rate (Hz) is approximately: "); Console.print(accel_rate); Console.print("\n");

    _imu.setGyroRateDivisor(IMU_GYROSCOPE_DIVISOR);
    float gyro_rate = 1100 / (1.0 + IMU_GYROSCOPE_DIVISOR);
    Console.print("Gyro data rate divisor set to: "); Console.print(IMU_GYROSCOPE_DIVISOR); Console.print("\n");
    Console.print("Gyro data rate (Hz) is approximately: "); Console.print(gyro_rate); Console.print("\n");

    _imu.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
    Console.println("Magnetometer data rate set to: 10 Hz");
}

IMU::IMUData IMU::getData() {
    IMU::IMUData data;
    _imu.getEvent(&data.accelerometer, &data.gyroscope, &data.temperature, &data.magnetometer);
    return data;
}

void IMU::printData(IMUData& data) {
    Console.print("Temp: "); Console.print(data.temperature.temperature); Console.print("*C  ");
    Console.print("Acc X: "); Console.print(data.accelerometer.acceleration.x); Console.print(" Y: "); Console.print(data.accelerometer.acceleration.y); Console.print(" Z: "); Console.print(data.accelerometer.acceleration.z); Console.print(" m/s^2  ");
    Console.print("Mag X: "); Console.print(data.magnetometer.magnetic.x); Console.print(" Y: "); Console.print(data.magnetometer.magnetic.y); Console.print(" Z: "); Console.print(data.magnetometer.magnetic.z); Console.print(" uT  ");
    Console.print("Gyro X: "); Console.print(data.gyroscope.gyro.x); Console.print(" Y: "); Console.print(data.gyroscope.gyro.y); Console.print(" Z: "); Console.print(data.gyroscope.gyro.z); Console.print(" rad/s  ");
}

void IMU::printData() {
    IMUData data = getData();;
    printData(data);
}
