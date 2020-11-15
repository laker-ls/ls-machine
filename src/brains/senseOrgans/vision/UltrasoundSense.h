#pragma once

#include "pinManagment/UltrasoundHC_SR04.h"

/**
 * Работа с ультразвуковым датчиком расстояния HC-SR04.
 */
class UltrasoundSense
{
    public:
        /** @param eye массив, где первый элемент trig, второй echo */
        void setPins(const uint8_t *eye);
        uint16_t distanceInCm();

    private:
        uint8_t trig;
        uint8_t echo;

        UltrasoundHC_SR04 UltrasoundHC_SR04Object;
};
