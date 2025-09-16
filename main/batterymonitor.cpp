#include "batterymonitor.h"

BatteryMonitor::BatteryMonitor() { _batterymonitor = Adafruit_INA228(); }

void BatteryMonitor::begin() {
    Console.println("Initialise Adafruit INA228");

    if (!_batterymonitor.begin()) {
        Console.println("Failed to find INA228 chip");
        return;
    }

    Console.println("Found INA228 chip\n");
    _batterymonitor.setShunt(INA228_SHUNT_RESISTANCE, INA228_MAX_CURRENT);

    _batterymonitor.setAveragingCount(INA228_COUNT_16);
    Console.print("Averaging counts: 16 samples\n");

    _batterymonitor.setVoltageConversionTime(INA228_TIME_150_us);
    Console.print("Voltage conversion time: "); Console.print(_batterymonitor.getVoltageConversionTime()); Console.print(" uS\n");

    _batterymonitor.setCurrentConversionTime(INA228_TIME_280_us);
    Console.print("Current conversion time: "); Console.print(_batterymonitor.getCurrentConversionTime()); Console.print(" uS\n");
}

BatteryMonitor::BatteryData BatteryMonitor::getData() {
    BatteryMonitor::BatteryData data;
    data.current = _batterymonitor.getCurrent_mA();
    data.voltage = _batterymonitor.getBusVoltage_V();
    data.shuntvoltage = _batterymonitor.getShuntVoltage_mV();
    data.power = _batterymonitor.getPower_mW();
    data.energy = _batterymonitor.readEnergy();
    data.charge = _batterymonitor.readCharge();
    data.temperature = _batterymonitor.readDieTemp();
    return data;
}

void BatteryMonitor::printData() {
    BatteryData data = getData();
    printData(data);
}

void BatteryMonitor::printData(BatteryData& data) {
    Console.print("A: "); Console.print(data.current); Console.print(" mA  ");
    Console.print("V: "); Console.print(data.voltage); Console.print(" V  ");
    Console.print("SV: "); Console.print(data.shuntvoltage); Console.print(" mV  ");
    Console.print("P: "); Console.print(data.power); Console.print(" mW  ");
    Console.print("E: "); Console.print(data.energy); Console.print(" J  ");
    Console.print("C: "); Console.print(data.charge); Console.print(" C  ");
    Console.print("Temp: "); Console.print(data.temperature); Console.print(" *C  ");
}
