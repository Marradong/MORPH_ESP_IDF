#include "controller.h"

BLEController* BLEController::instance = nullptr;

BLEController::BLEController() {
    instance = this;
    ctrl = nullptr;
}

void BLEController::begin() {
    Console.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Console.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    BP32.setup(&onConnected, &onDisconnected, true);
    BP32.enableBLEService(false);
}

void BLEController::onConnected(ControllerPtr ctl) {
    if (instance) instance->_onConnected(ctl);  // forward to the real instance
}

void BLEController::_onConnected(ControllerPtr ctl) {
    bool foundEmptySlot = false;

    if (ctrl == nullptr) {
        Console.print("CALLBACK: Controller is connected\n");
        ControllerProperties properties = ctl->getProperties();
        Console.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName(), properties.vendor_id,
                        properties.product_id);
        ctrl = ctl;
        foundEmptySlot = true;
    }

    if (!foundEmptySlot) {
        Console.println("CALLBACK: Controller connected, but could not find empty slot");
    }
}

void BLEController::onDisconnected(ControllerPtr ctl) {
    if (instance) instance->_onDisconnected(ctl);  // forward to the real instance
}

void BLEController::_onDisconnected(ControllerPtr ctl) {
    bool foundController = false;

    if (ctrl == ctl) {
        Console.print("CALLBACK: Controller disconnected\n");
        ctrl = nullptr;
        foundController = true;
    }

    if (!foundController) {
        Console.println("CALLBACK: Controller disconnected, but not found");
    }
}

void BLEController::print() {
    if (ctrl == nullptr) {
        return;
    }

    Console.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, trigger L: %4d, trigger R: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctrl->index(),        // Controller Index
        ctrl->dpad(),         // D-pad
        ctrl->buttons(),      // bitmask of pressed buttons
        ctrl->axisX(),        // (-511 - 512) left X Axis
        ctrl->axisY(),        // (-511 - 512) left Y axis
        ctrl->axisRX(),       // (-511 - 512) right X axis
        ctrl->axisRY(),       // (-511 - 512) right Y axis
        ctrl->brake(),     // (0 - 1023): trigger L button
        ctrl->throttle(),     // (0 - 1023): trigger R button
        ctrl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctrl->gyroX(),        // Gyro X
        ctrl->gyroY(),        // Gyro Y
        ctrl->gyroZ(),        // Gyro Z
        ctrl->accelX(),       // Accelerometer X
        ctrl->accelY(),       // Accelerometer Y
        ctrl->accelZ()        // Accelerometer Z
    );
}

void BLEController::process() {
    if (!BP32.update()){
        return;
    }

    if (ctrl && ctrl->isConnected() && ctrl->hasData()) {
        if (ctrl->isGamepad()) {
            // print();
        }
    }
}

bool BLEController::home() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->miscButtons() == 0x01;
}

bool BLEController::restart() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->miscButtons() == 0x08;
}

bool BLEController::left() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x08;
}

bool BLEController::right() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x04;
}

bool BLEController::forward() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x01;
}

bool BLEController::backward() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x02;
}

bool BLEController::stopped() {
    if (ctrl == nullptr) {
        return false;
    }
    return !forward() && !backward() && !left() && !right() && !home() && !restart() && !up() && !down();
}

bool BLEController::up() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->throttle() >= 512;
}

bool BLEController::down() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->brake() >= 512;
}

uint32_t BLEController::leftRight() {
    if (ctrl == nullptr) {
        return 0;
    }
    return ctrl->axisX();
}

uint32_t BLEController::upDown() {
    if (ctrl == nullptr) {
        return 0;
    }
    return ctrl->axisY();
}