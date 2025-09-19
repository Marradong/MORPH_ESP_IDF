#include "batterymonitor.h"

BatteryMonitor::BatteryMonitor() : _batterymonitor(Adafruit_INA228()) {}

void BatteryMonitor::begin() {
    Console.println("Initialise Adafruit INA228");

    if (!_batterymonitor.begin()) {
        Console.println("Failed to find INA228 chip");
        return;
    }

    Console.println("Found INA228 chip\n");

    _batterymonitor.setShunt(INA228_SHUNT_RESISTANCE, INA228_MAX_CURRENT);
    _batterymonitor.setAveragingCount(INA228_COUNT_16);
    _batterymonitor.setVoltageConversionTime(INA228_TIME_150_us);
    _batterymonitor.setCurrentConversionTime(INA228_TIME_280_us);
}

void BatteryMonitor::getData(BatteryData& data) {
    data.current = _batterymonitor.getCurrent_mA();
    data.voltage = _batterymonitor.getBusVoltage_V();
    data.shuntvoltage = _batterymonitor.getShuntVoltage_mV();
    data.power = _batterymonitor.getPower_mW();
    data.energy = _batterymonitor.readEnergy();
    data.charge = _batterymonitor.readCharge();
    data.temperature = _batterymonitor.readDieTemp();
}

void BatteryMonitor::printData(BatteryData& data) {
    Console.printf("\nA: %d mA  ", data.current);
    Console.printf("V: %d V  ", data.voltage);
    Console.printf("SV: %d mV  ", data.shuntvoltage);
    Console.printf("P: %d mW  ", data.power);
    Console.printf("E: %d J  ", data.energy);
    Console.printf("C: %d C  ", data.charge);
    Console.printf("Temp: %d *C  ", data.temperature);
}
