#include "pinManagment/UltrasoundHC_SR04.h"

void UltrasoundHC_SR04::setPins(uint8_t trig, uint8_t echo)
{
    this->trig = trig;
    this->echo = echo;

    pinMode (this->trig, OUTPUT);
    pinMode (this->echo, INPUT);
}

void UltrasoundHC_SR04::digitalTrig(bool value)
{
    digitalWrite(this->trig, value);
}

uint32_t UltrasoundHC_SR04::pulseInEcho(bool value, uint32_t timeout)
{
    return pulseIn(this->echo, value, timeout);
}