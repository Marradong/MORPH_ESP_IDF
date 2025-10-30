#include "imu.h"

IMU::IMU() : _imu(Adafruit_ICM20948()), _initialised(false) {}

void IMU::begin() {
    Console.println("Initialise Adafruit ICM20948");

    if (!_imu.begin_I2C()) {
        Console.println("Failed to find ICM20948 chip");
        _initialised = false;
        return;
    }

    Console.println("Found ICM20948 chip");
    
    _imu.setAccelRange(ICM20948_ACCEL_RANGE_4_G);
    _imu.setGyroRange(ICM20948_GYRO_RANGE_500_DPS);
    _imu.setAccelRateDivisor(IMU_ACCELEROMETER_DIVISOR);
    _imu.setGyroRateDivisor(IMU_GYROSCOPE_DIVISOR);
    _imu.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);

    _initialised = true;
}

bool IMU::isInitialised() {
    return _initialised;
}

void IMU::getData(IMUData& data) {
    _imu.getEvent(&data.accelerometer, &data.gyroscope, &data.temperature, &data.magnetometer);
}

void IMU::printData(IMUData& data) {
    Console.printf("\nTemp: %d *C  ", data.temperature.temperature);
    Console.printf("Acc X: %d Y: %d Z: %d m/s^2  ", data.accelerometer.acceleration.x, data.accelerometer.acceleration.y, data.accelerometer.acceleration.z);
    Console.printf("Mag X: %d Y: %d Z: %d uT  ", data.magnetometer.magnetic.x, data.magnetometer.magnetic.y, data.magnetometer.magnetic.z);
    Console.printf("Gyro X: %d Y: %d Z: %d rad/s  ", data.gyroscope.gyro.x, data.gyroscope.gyro.y, data.gyroscope.gyro.z);
}