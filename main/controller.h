#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "sdkconfig.h"
#include <Bluepad32.h>

class BLEController {
public:
    struct BLEControllerData {
        bool home;
        bool restart;
        bool left;
        bool right;
        bool forward;
        bool backward;
        bool stopped;
        bool legUp;
        bool legDown;
        bool stepUp;
        bool stepDown;
        bool changeTrajectory;
        uint32_t leftRight;
        uint32_t upDown;
    };

    BLEController();

    void begin();
    void printData(BLEControllerData& data);
    void getData(BLEControllerData& data);
    bool isConnected();
    

private:
    ControllerPtr ctrl;
    void _onConnected(ControllerPtr ctl);
    void _onDisconnected(ControllerPtr ctl);

    static void onConnected(ControllerPtr ctl);
    static void onDisconnected(ControllerPtr ctl);

    static BLEController* instance;
};

#endif