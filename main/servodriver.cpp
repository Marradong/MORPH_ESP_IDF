#include "servodriver.h"

constexpr uint16_t ServoDriver::SERVO_MAX_PULSE[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_MIN_PULSE[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_TOP[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_BOTTOM[SERVO_NUMBER];

ServoDriver::ServoDriver() { _servodriver = Adafruit_PWMServoDriver(); }

void ServoDriver::begin(){
    Console.println("Initialise Adafruit PCA9685");

    if (!_servodriver.begin()) {
        Console.println("Failed to find PCA9685 chip");
        return;
    }

    _servodriver.reset();
    Console.print("PCA9685 chip reset\n");

    _servodriver.setOutputMode(true);
    Console.print("Set output mode to push / pull\n");

    _servodriver.setOscillatorFrequency(OSCILLATOR_FREQUENCY);
    Console.print("Oscillator frequency set to: "); Console.print(OSCILLATOR_FREQUENCY); Console.print(" Hz\n");

    _servodriver.setPWMFreq(SERVO_FREQUENCY);
    Console.print("Servo frequency set to: "); Console.print(SERVO_FREQUENCY); Console.print(" Hz\n");
}

void ServoDriver::driveServo(uint8_t servo, double angle) {
    long pulse = pulseFromAngle(servo, angle);

    if (pulse < 0) {
        return;
    }
    
    _servodriver.setPin(servo, pulse);
}

long ServoDriver::pulseFromAngle(uint8_t servo, double angle) {
    if (servo < 0 || servo >= SERVO_NUMBER || angle < 0 || angle > SERVO_MAX_ANGLE) {
        return -1;
    }

    return map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_BOTTOM[servo], SERVO_TOP[servo]);
}