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
        VL53L0X sensorLeft;
        VL53L0X sensorRight;

        //#define LONG_RANGE;

        Laser()
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
            sensorLeft.setAddress(I2S_LEFT);

            pinMode(LASER_RIGHT, INPUT);
            sensorRight.init(true);
            
            sensorRight.setAddress(I2S_RIGHT);
        }

        /**
         * Расстояние до препятствия, с углом, под которым находится препятствие. При отсутствии препятствий возвращается 999.
         * @return в индексе 0 хранится расстояние в сантиметрах, в индексе 1 хранится угол препятствия.
         */
        uint16_t* distanceWithAngle()
        {
            uint16_t distanceLeft = sensorLeft.readRangeSingleMillimeters();
            uint16_t distanceRight = sensorRight.readRangeSingleMillimeters();
            uint16_t distance;

            uint16_t* result = new uint16_t[3];

            if (distanceLeft < distanceRight) {
                distance = distanceLeft;
            } else {
                distance = distanceRight;
            }

            result[0] = convertInCmWithMaxRange(distance);
            result[1] = angleOfObject(distanceLeft, distanceRight);

            return result;
        }
    private:
        const uint8_t I2S_LEFT = 25;
        const uint8_t I2S_RIGHT = 22;

        /**
         * Преобразование расстояния из миллиметров в сантиметры. Так же при отстутствия препятствий возвращается 999.
         * @param distance расстояние в миллиметрах.
         * @return расстояние в сантиметрах.
         */
        int16_t convertInCmWithMaxRange(uint16_t distance)
        {
            uint16_t distanceWithLimit = limitDistance(distance);

            return (distanceWithLimit / 10);
        }

        /**
         * Определение угла препятствия.
         * @param laserLeft расстояние на левом датчике.
         * @param laserRight расстояние на правом датчике.
         * @return угол, под которым находится препятствие.
         */
        int16_t angleOfObject(float laserLeft, float laserRight)
        {
            int16_t degree;

            if (laserLeft < LASER_DISTANCE_LIMIT && laserRight < LASER_DISTANCE_LIMIT) {
                float a = laserLeft - laserRight;
                float b = DISTANCE_BETWEEN_LASER;
                float tang = (a / b);
                float radian = atan(tang);

                degree = radian * 57.3;
            } else {
                degree = 0;
            }
            
            return degree;
        }

        /**
         * Обрезка показаний датчика, при значении превышающем максимальное расстояние возвращает 9999.
         * @param distance расстояние в миллиметрах
         * @return расстояние в диапазоне дозволенного, значения превышающие максимальное расстояние возвращаются в виде 9999.
         */
        uint16_t limitDistance(uint16_t distance)
        {
            uint16_t result;
            if (distance < LASER_DISTANCE_LIMIT) {
                result = distance;
            } else {
                result = 9999;
            }

            return result;
        }
};
