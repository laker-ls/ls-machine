#include "main.h"

void Laser::init()
{
    pinMode(LASER_LEFT, OUTPUT);
    pinMode(LASER_RIGHT, OUTPUT);
    digitalWrite(LASER_LEFT, LOW);
    digitalWrite(LASER_RIGHT, LOW);

    Wire.begin();

    sensorLeft.setTimeout(500);
    sensorRight.setTimeout(500);

    pinMode(LASER_LEFT, INPUT);
    sensorLeft.init(true);
    sensorLeft.setAddress((uint8_t)1);

    pinMode(LASER_RIGHT, INPUT);
    sensorRight.init(true);
    sensorRight.setAddress((uint8_t)2);
}

uint16_t Laser::distanceLeftInCm()
{
    uint16_t distanceLeftRaw = distanceRaw(sensorLeft);
    return distanceInCmWithLimit(distanceLeftRaw);
}

uint16_t Laser::distanceRightInCm()
{
    uint16_t distanceRightRaw = distanceRaw(sensorRight);
    return distanceInCmWithLimit(distanceRightRaw);
}

int16_t Laser::angleOfObject(uint16_t laserLeft, uint16_t laserRight)
{
    int16_t degree = 0;

    if (laserLeft < LASER_DISTANCE_LIMIT && laserRight < LASER_DISTANCE_LIMIT) {
        float a = laserLeft - laserRight;
        float b = DISTANCE_BETWEEN_LASER;
        float tang = (a / b);
        float radian = atan(tang);

        degree = radian * 57.3;
    }
    
    return degree;
}

uint16_t Laser::distanceRaw(VL53L0X sensor)
{
    uint16_t distanceRaw = 9999;

    if (!sensor.timeoutOccurred()) {
        distanceRaw = sensor.readRangeSingleMillimeters();
    }

    return distanceRaw;
}

uint16_t Laser::distanceInCmWithLimit(uint16_t distanceRaw)
{
    uint16_t result = 9999;

    if (!sensorLeft.timeoutOccurred()) {
        result = limitDistance(distanceRaw);
    }

    return convertInCmWithMaxRange(result);
}

uint16_t Laser::convertInCmWithMaxRange(uint16_t distance)
{
    return (distance / 10);
}

uint16_t Laser::limitDistance(uint16_t distance)
{
    uint16_t result = 9999;

    if (distance < LASER_DISTANCE_LIMIT) {
        result = distance;
    }

    return result;
}
