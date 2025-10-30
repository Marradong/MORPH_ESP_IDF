#include "controller.h"

BLEController* BLEController::instance = nullptr;

BLEController::BLEController() : ctrl(nullptr) { instance = this; }

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

bool BLEController::isConnected() {
    return (ctrl != nullptr) && ctrl->isConnected();
}

void BLEController::printData(BLEControllerData& data) {
    if (ctrl == nullptr) {
        return;
    }

    Console.printf(
        "idx: %d, home: %d, restart: %d, left: %d, right: %d, forward: %d, backward: %d, legUp: %d, legDown: %d, stepUp: %d, stepDown: %d, changeTrajectory: %d, stopped: %d, x-axis: %4d, y-axis: %4d\n",
        data.home,
        data.restart,
        data.left,
        data.right,
        data.forward,
        data.backward,
        data.legUp,
        data.legDown,
        data.stepUp,
        data.stepDown,
        data.changeTrajectory,
        data.stopped,
        data.leftRight,
        data.upDown
    );
}

void BLEController::getData(BLEControllerData& data) {
    if (!BP32.update()){
        return;
    }

    if (ctrl && ctrl->isConnected() && ctrl->hasData()) {
        if (ctrl->isGamepad()) {
            data.home = ctrl->miscButtons() == 0x01;
            data.restart = ctrl->miscButtons() == 0x08;
            data.left = ctrl->dpad() == 0x08;
            data.right = ctrl->dpad() == 0x04;
            data.forward = ctrl->dpad() == 0x01;
            data.backward = ctrl->dpad() == 0x02;
            data.legUp = ctrl->throttle() >= 512;
            data.legDown = ctrl->brake() >= 512;
            data.stepUp = ctrl->buttons() == 0x0010;
            data.stepDown = ctrl->buttons() == 0x0020;
            data.changeTrajectory = ctrl->buttons() == 0x0008;
            data.stopped = !data.forward && !data.backward && !data.left && !data.right && !data.home && !data.restart && !data.legUp && !data.legDown && !data.stepUp && !data.stepDown && !data.changeTrajectory;
            data.leftRight = ctrl->axisX();
            data.upDown = ctrl->axisY();
        }
        else if (ctrl->isKeyboard()) {
            data.home = ctrl->isKeyPressed(Keyboard_H);
            data.restart = ctrl->isKeyPressed(Keyboard_R);
            data.left = ctrl->isKeyPressed(Keyboard_LeftArrow) || ctrl->isKeyPressed(Keyboard_A);
            data.right = ctrl->isKeyPressed(Keyboard_RightArrow) || ctrl->isKeyPressed(Keyboard_D);
            data.forward = ctrl->isKeyPressed(Keyboard_UpArrow) || ctrl->isKeyPressed(Keyboard_W);
            data.backward = ctrl->isKeyPressed(Keyboard_DownArrow) || ctrl->isKeyPressed(Keyboard_S);
            data.legUp = ctrl->isKeyPressed(Keyboard_Q);
            data.legDown = ctrl->isKeyPressed(Keyboard_E);
            data.stepUp = ctrl->isKeyPressed(Keyboard_Z);
            data.stepDown = ctrl->isKeyPressed(Keyboard_X);
            data.changeTrajectory = ctrl->isKeyPressed(Keyboard_T);
            data.stopped = !data.forward && !data.backward && !data.left && !data.right && !data.home && !data.restart && !data.legUp && !data.legDown && !data.stepUp && !data.stepDown && !data.changeTrajectory;
            data.leftRight = 0;
            data.upDown = 0;
        }
    }
}