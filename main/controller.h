#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "sdkconfig.h"
#include <Arduino.h>
#include <Bluepad32.h>

class BLEController {
public:
    BLEController();

    void begin();
    void print();
    void process();
    bool home();
    bool restart();
    bool left();
    bool right();
    bool forward();
    bool backward();
    bool stopped();
    bool up();
    bool down();
    uint32_t leftRight();
    uint32_t upDown();

private:
    ControllerPtr ctrl;
    void _onConnected(ControllerPtr ctl);
    void _onDisconnected(ControllerPtr ctl);

    static void onConnected(ControllerPtr ctl);
    static void onDisconnected(ControllerPtr ctl);

    static BLEController* instance;
};

#endif