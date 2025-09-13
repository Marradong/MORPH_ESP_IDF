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

private:
    ControllerPtr ctrl;
    void _onConnected(ControllerPtr ctl);
    void _onDisconnected(ControllerPtr ctl);

    static void onConnected(ControllerPtr ctl);
    static void onDisconnected(ControllerPtr ctl);

    static BLEController* instance;
};

#endif