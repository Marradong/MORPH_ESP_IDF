#include "batterymonitor.h"

BatteryMonitor::BatteryMonitor() { _batterymonitor = Adafruit_INA228(); }

void BatteryMonitor::begin() {
    Serial.println("Initialise Adafruit INA228");

    if (!_batterymonitor.begin()) {
        Serial.println("Failed to find INA228 chip");
        return;
    }

    Serial.println("Found INA228 chip\n");
    _batterymonitor.setShunt(INA228_SHUNT_RESISTANCE, INA228_MAX_CURRENT);

    _batterymonitor.setAveragingCount(INA228_COUNT_16);
    Serial.print("Averaging counts: 16 samples\n");

    _batterymonitor.setVoltageConversionTime(INA228_TIME_150_us);
    Serial.print("Voltage conversion time: "); Serial.print(_batterymonitor.getVoltageConversionTime()); Serial.print(" uS\n");

    _batterymonitor.setCurrentConversionTime(INA228_TIME_280_us);
    Serial.print("Current conversion time: "); Serial.print(_batterymonitor.getCurrentConversionTime()); Serial.print(" uS\n");
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
    Serial.print("Current: "); Serial.print(data.current, 3); Serial.print(" mA\n");
    Serial.print("Voltage: "); Serial.print(data.voltage, 3); Serial.print(" V\n");
    Serial.print("Shunt Voltage: "); Serial.print(data.shuntvoltage, 3); Serial.print(" mV\n");
    Serial.print("Power: "); Serial.print(data.power, 3); Serial.print(" mW\n");
    Serial.print("Energy: "); Serial.print(data.energy, 3); Serial.print(" J\n");
    Serial.print("Charge: "); Serial.print(data.charge, 3); Serial.print(" C\n");
    Serial.print("Temperature: "); Serial.print(data.temperature, 3); Serial.print(" *C\n");
    Serial.println();
}
