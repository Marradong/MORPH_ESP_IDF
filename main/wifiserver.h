#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <ArduinoJson.h>
#include <ArduinoConsole.h>
#include <WiFi.h>
#include "WIFIConfig.h"
#include "imu.h"
#include "controller.h"
#include "batterymonitor.h"

class WIFIServer {
public:
    WIFIServer();
    void begin();
    void handleClient(BLEController::BLEControllerData& c, IMU::IMUData& i, BatteryMonitor::BatteryData& b);

private:
    WiFiServer server;
    WiFiClient webClient;
    String clientRequest;
};

#endif