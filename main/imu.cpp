#include "imu.h"

IMU::IMU() { _imu = Adafruit_ICM20948(); }

void IMU::begin() {
    Serial.println("Initialise Adafruit ICM20948");

    if (!_imu.begin_I2C()) {
        Serial.println("Failed to find ICM20948 chip");
        return;
    }

    Serial.println("Found ICM20948 chip");
    
    _imu.setAccelRange(ICM20948_ACCEL_RANGE_4_G);
    Serial.println("Accelerometer range set to: +-4 G");

    _imu.setGyroRange(ICM20948_GYRO_RANGE_500_DPS);
    Serial.println("Gyro range set to: 500 degrees/s");

    _imu.setAccelRateDivisor(IMU_ACCELEROMETER_DIVISOR);
    float accel_rate = 1125 / (1.0 + IMU_ACCELEROMETER_DIVISOR);
    Serial.print("Accelerometer data rate divisor set to: "); Serial.print(IMU_ACCELEROMETER_DIVISOR); Serial.print("\n");
    Serial.print("Accelerometer data rate (Hz) is approximately: "); Serial.print(accel_rate); Serial.print("\n");

    _imu.setGyroRateDivisor(IMU_GYROSCOPE_DIVISOR);
    float gyro_rate = 1100 / (1.0 + IMU_GYROSCOPE_DIVISOR);
    Serial.print("Gyro data rate divisor set to: "); Serial.print(IMU_GYROSCOPE_DIVISOR); Serial.print("\n");
    Serial.print("Gyro data rate (Hz) is approximately: "); Serial.print(gyro_rate); Serial.print("\n");

    _imu.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
    Serial.println("Magnetometer data rate set to: 10 Hz");
}

IMU::IMUData IMU::getData() {
    IMU::IMUData data;
    _imu.getEvent(&data.accelerometer, &data.gyroscope, &data.temperature, &data.magnetometer);
    return data;
}

void IMU::printData(IMUData& data) {
    Serial.print("Temperature "); Serial.print(data.temperature.temperature, 3); Serial.print(" *C\n");
    Serial.print("Acceleration X: "); Serial.print(data.accelerometer.acceleration.x, 3); Serial.print(" Y: "); Serial.print(data.accelerometer.acceleration.y, 3); Serial.print(" Z: "); Serial.print(data.accelerometer.acceleration.z, 3); Serial.print(" m/s^2\n");
    Serial.print("Mag X: "); Serial.print(data.magnetometer.magnetic.x, 3); Serial.print(" Y: "); Serial.print(data.magnetometer.magnetic.y, 3); Serial.print(" Z: "); Serial.print(data.magnetometer.magnetic.z, 3); Serial.print(" uT\n");
    Serial.print("Gyro X: "); Serial.print(data.gyroscope.gyro.x, 3); Serial.print(" Y: "); Serial.print(data.gyroscope.gyro.y, 3); Serial.print(" Z: "); Serial.print(data.gyroscope.gyro.z, 3); Serial.print(" radians/s\n");
    Serial.println();
}

void IMU::printData() {
    IMUData data = getData();;
    printData(data);
}
