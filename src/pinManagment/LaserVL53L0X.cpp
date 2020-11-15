#include "LaserVL53L0X.h"

void LaserVL53L0X::enableSensor(uint8_t pinXSHUT)
{
    pinMode(pinXSHUT, OUTPUT);
    digitalWrite(pinXSHUT, HIGH);
}
