#include "main.h"

void UltrasoundSense::setPins(const uint8_t *eye)
{
    trig = eye[0];
    echo = eye[1];

    this->UltrasoundHC_SR04Object.setPins(trig, echo);
}

uint16_t UltrasoundSense::distanceInCm()
{
    uint16_t duration, cm;

    this->UltrasoundHC_SR04Object.digitalTrig(LOW);
    delayMicroseconds(2);
    this->UltrasoundHC_SR04Object.digitalTrig(HIGH);
    delayMicroseconds(10);
    this->UltrasoundHC_SR04Object.digitalTrig(LOW);
    
    duration = this->UltrasoundHC_SR04Object.pulseInEcho(HIGH, 23200); // 23200 = 400см.
    if (duration == 0) {
        cm = 999;
    } else {
        cm = (duration / 2) / 29;
    }

    return cm;
}
