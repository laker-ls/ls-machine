#pragma once
#include <Arduino.h>
#include "Characteristics.h"
#include <Wire.h>
#include <VL53L0X.h>

/**
 * Работа с лазерным датчиком расстояния VL53L0X. 
 */
class Laser
{
    public:
        void init()
        {
            pinMode(LASER_LEFT, OUTPUT);
            pinMode(LASER_RIGHT, OUTPUT);
            digitalWrite(LASER_LEFT, LOW);
            digitalWrite(LASER_RIGHT, LOW);

            Wire.begin();

            sensorLeft.setTimeout(500);
            sensorRight.setTimeout(500);

            // pinMode(LASER_LEFT, INPUT);
            // sensorLeft.init(true);
            // sensorLeft.setAddress((uint8_t)1);

            pinMode(LASER_RIGHT, INPUT);
            sensorRight.init(true);
            // sensorRight.setAddress((uint8_t)2);
        }

        /**
         * @return Расстояние левого лазерного датчика до препятствия в сантиметрах. При отсутствии препятствия возвращается 999.
         */
        uint16_t distanceLeftInCm()
        {
            uint16_t distanceLeftRaw = distanceRaw(sensorLeft);
            return distanceInCmWithLimit(distanceLeftRaw);
        }

        /**
         * @return Расстояние правого лазерного датчика до препятствия в сантиметрах. При отсутствии препятствия возвращается 999.
         */
        uint16_t distanceRightInCm()
        {
            uint16_t distanceRightRaw = distanceRaw(sensorRight);
            return distanceInCmWithLimit(distanceRightRaw);
        }

        /**
         * Определение угла препятствия.
         * @param laserLeft расстояние на левом датчике.
         * @param laserRight расстояние на правом датчике.
         * @return угол, под которым находится препятствие.
         */
        int16_t angleOfObject(uint16_t laserLeft, uint16_t laserRight)
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

    private:
        VL53L0X sensorLeft;
        VL53L0X sensorRight;

        /**
         * @param sensor объект датчика VL53L0X.
         * @return Расстояние до препятствия в миллиметрах.
         */
        uint16_t distanceRaw(VL53L0X sensor)
        {
            uint16_t distanceRaw = 9999;

            if (!sensor.timeoutOccurred()) {
                distanceRaw = sensor.readRangeSingleMillimeters();
            }

            return distanceRaw;
        }

        /**
         * @param distanceRaw расстояние в миллиметрах.
         * @return Расстояние в сантиметрах, если превышен лимит расстояния (смотрите в файле основных характеристик) возвращается 999.
         */
        uint16_t distanceInCmWithLimit(uint16_t distanceRaw)
        {
            uint16_t result = 9999;

            if (!sensorLeft.timeoutOccurred()) {
                result = limitDistance(distanceRaw);
            }

            return convertInCmWithMaxRange(result);
        }

        /**
         * Преобразование расстояния из миллиметров в сантиметры. Так же при отстутствия препятствий возвращается 999.
         * @param distance расстояние в миллиметрах.
         * @return расстояние в сантиметрах.
         */
        uint16_t convertInCmWithMaxRange(uint16_t distance)
        {
            return (distance / 10);
        }

        /**
         * Обрезка показаний датчика, при значении превышающем максимальное расстояние возвращает 9999.
         * @param distance расстояние в миллиметрах
         * @return расстояние в диапазоне дозволенного, значения превышающие максимальное расстояние возвращаются в виде 9999.
         */
        uint16_t limitDistance(uint16_t distance)
        {
            uint16_t result = 9999;

            if (distance < LASER_DISTANCE_LIMIT) {
                result = distance;
            }

            return result;
        }
};
