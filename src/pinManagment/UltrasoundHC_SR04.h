#pragma once

#include <Arduino.h>

class UltrasoundHC_SR04
{
    public:
        void setPins(uint8_t trig, uint8_t echo);
        void digitalTrig(bool value);
        uint32_t pulseInEcho(bool value, uint32_t timeout);

    private:
        uint8_t trig;
        uint8_t echo;
};
