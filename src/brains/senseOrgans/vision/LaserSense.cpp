#include "LaserSense.h"

void LaserSense::init(uint8_t pinXSHUT)
{
    LaserVL53L0XObject.enableSensor(pinXSHUT);
    Wire.begin();
    sensor.init(true);
    sensor.setAddress(pinXSHUT);
    sensor.setTimeout(500);

    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 16);
    sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 12);

    sensor.startContinuous();
}

uint16_t LaserSense::distanceInCm()
{
    uint16_t result;
    uint16_t distanceInMm = this->sensor.readRangeContinuousMillimeters();

    result = (distanceInMm / 10);
    if (result > MAX_RANGE_CM) {
        result = 999;
    }

    return result;
}
