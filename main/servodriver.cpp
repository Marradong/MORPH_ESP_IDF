#include "servodriver.h"

constexpr uint16_t ServoDriver::SERVO_MAX_PULSE[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_MIN_PULSE[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_TOP[SERVO_NUMBER];
constexpr uint16_t ServoDriver::SERVO_BOTTOM[SERVO_NUMBER];

ServoDriver::ServoDriver() { _servodriver = Adafruit_PWMServoDriver(); }

void ServoDriver::begin(){
    Serial.println("Initialise Adafruit PCA9685");

    if (!_servodriver.begin()) {
        Serial.println("Failed to find PCA9685 chip");
        return;
    }

    _servodriver.reset();
    Serial.print("PCA9685 chip reset\n");

    _servodriver.setOutputMode(true);
    Serial.print("Set output mode to push / pull\n");

    _servodriver.setOscillatorFrequency(OSCILLATOR_FREQUENCY);
    Serial.print("Oscillator frequency set to: "); Serial.print(OSCILLATOR_FREQUENCY); Serial.print(" Hz\n");

    _servodriver.setPWMFreq(SERVO_FREQUENCY);
    Serial.print("Servo frequency set to: "); Serial.print(SERVO_FREQUENCY); Serial.print(" Hz\n");
}

void ServoDriver::driveServo(uint8_t servo, double angle) {
    long pulse = pulseFromAngle(servo, angle);

    if (pulse < 0) {
        return;
    }
    
    Serial.print("Setting servo "); Serial.print(servo); Serial.print(" pulse to "); Serial.print(pulse); Serial.print(" out of 4096\n");

    _servodriver.setPin(servo, pulse);
}

void ServoDriver::driveServo(uint8_t servo, uint16_t pwm) {
    if (pwm < 0 || pwm > 4095) {
        return;
    }

    Serial.print("Setting servo "); Serial.print(servo); Serial.print(" pulse to "); Serial.print(pwm); Serial.print(" out of 4096\n");

    _servodriver.setPin(servo, pwm);
}

long ServoDriver::pulseFromAngle(uint8_t servo, double angle) {
    if (servo < 0 || servo >= SERVO_NUMBER || angle < 0 || angle > SERVO_MAX_ANGLE) {
        return -1;
    }

    return map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_BOTTOM[servo], SERVO_TOP[servo]);
}

void ServoDriver::sweepServo(uint8_t servo) {
    if (servo < 0 || servo >= SERVO_NUMBER) {
        return;
    }
    
    Serial.print("Sweeping servo "); Serial.print(servo); Serial.print(" forward\n");
    for (uint16_t pulselen = SERVO_MIN_PULSE[servo]; pulselen <= SERVO_MAX_PULSE[servo]; pulselen+=2) {
        driveServo(servo, pulselen);
        delay(10);
    }
    

    Serial.print("Sweeping servo "); Serial.print(servo); Serial.print(" back\n");
    for (uint16_t pulselen = SERVO_MAX_PULSE[servo]; pulselen >= SERVO_MIN_PULSE[servo]; pulselen-=2) {
        driveServo(servo, pulselen);
        delay(10);
    }
}

void ServoDriver::driveToBottom(uint8_t servo) {
    if (servo < 0 || servo >= SERVO_NUMBER) {
        return;
    }

    Serial.print("Driving servo "); Serial.print(servo); Serial.print(" to bottom\n");
    driveServo(servo, SERVO_BOTTOM[servo]);
}

void ServoDriver::driveToTop(uint8_t servo) {
    if (servo < 0 || servo >= SERVO_NUMBER) {
        return;
    }

    Serial.print("Driving servo "); Serial.print(servo); Serial.print(" to top\n");
    driveServo(servo, SERVO_TOP[servo]);
}