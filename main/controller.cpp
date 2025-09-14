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

    // Setup the Bluepad32 callbacks, and the default behavior for scanning or not.
    // By default, if the "startScanning" parameter is not passed, it will do the "start scanning".
    // Notice that "Start scanning" will try to auto-connect to devices that are compatible with Bluepad32.
    // E.g: if a Gamepad, keyboard or mouse are detected, it will try to auto connect to them.
    bool startScanning = true;
    BP32.setup(&onConnected, &onDisconnected, startScanning);

    // Enables the BLE Service in Bluepad32.
    // This service allows clients, like a mobile app, to setup and see the state of Bluepad32.
    // By default, it is disabled.
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

void BLEController::_onDisconnected(ControllerPtr ctl) {
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
        ctrl->triggerL(),     // (0 - 1023): trigger L button
        ctrl->triggerR(),     // (0 - 1023): trigger R button
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
            print();
        }
    }
}

bool BLEController::home() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->miscButtons() == 0x01;
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

bool BLEController::up() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x01;
}

bool BLEController::down() {
    if (ctrl == nullptr) {
        return false;
    }
    return ctrl->dpad() == 0x02;
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