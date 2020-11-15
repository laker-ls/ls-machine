#pragma once

#include <Wire.h>
#include <VL53L0X.h>
#include "pinManagment/LaserVL53L0X.h"

/**
 * Работа с лазерным датчиком расстояния VL53L0X. 
 */
class LaserSense
{
    public:
        void init(uint8_t pinXSHUT);

        /** 
         * Расстояние в сантиметрах. 
         * Если препятствие дальше MAX_RANGE_CM, возвращается 999.
         */
        uint16_t distanceInCm();

    private:
        const uint8_t MAX_RANGE_CM = 120;

        VL53L0X sensor;
        LaserVL53L0X LaserVL53L0XObject;
};
