#include "main.h"

void LaserSense::init(uint8_t pinXSHUT)
{
    LaserVL53L0XObject.enableSensor(pinXSHUT);
    Wire.begin();
    sensor.init(true);
    sensor.setAddress(pinXSHUT);
    sensor.setTimeout(500);
}

uint16_t LaserSense::distanceInCm()
{
    uint16_t result;

    result = (this->sensor.readRangeSingleMillimeters() / 10);
    if (result > MAX_RANGE_CM) {
        result = 999;
    }

    return result;
}
