#pragma once
#include <Arduino.h>
#include "Characteristics.h"

/**
 * Методы для рассчетов векторных значений.
 */
class Vector
{
    public:
        /** 
         * Обороты в минуту. В одном вольте 55 оборотов.
         */
        uint16_t rpm(uint8_t pwm)
        {
            const float VOLT_IN_ONE_PWM = (MOTOR_VOLTAGE / 255);
            const uint8_t rpmInOneVolt = 55;

            float volt = pwm * VOLT_IN_ONE_PWM;

            return volt * rpmInOneVolt;
        }

        /**
         * Расстояние в сантиметрах за секунду.
         */
        uint8_t centimetersPerSecond(uint8_t pwm)
        {
            return rpm(pwm) / 60 * circumference(WHEEL_DIAMETER);
        }

        /** 
         * Радиус поворота стороны, которая имеет МЕНЬШУЮ скорость.
         * Пример: Если левая стороная движется быстрее правой, то данная формула дает радиус движения ПРАВОЙ стороны.
         * 
         * @param sideFaster скорость сантиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость сантиметров в секунду борта имеющего меньшую скорость движения
         * @return радиус разворота в милиметрах
         */
        uint16_t radiusTurnSlowSide(uint8_t sideFaster, uint8_t sideSlow)
        {
            return sideSlow / (sideFaster - sideSlow) * BODY_WIDTH;
        }

        /** 
         * Радиус поворота стороны, которая имеет БОЛЬШУЮ скорость.
         * Пример: Если левая стороная движется быстрее правой, то данная формула дает радиус движения ЛЕВОЙ стороны.
         * 
         * @param sideFaster скорость сантиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость сантиметров в секунду борта имеющего меньшую скорость движения
         * @return радиус разворота в милиметрах
         */
        uint16_t radiusTurnFasterSide(uint8_t sideFaster, uint8_t sideSlow)
        {
            return sideFaster / (sideFaster - sideSlow) * BODY_WIDTH;
        }

        /** 
         * Радиус поворота центра транспорта. Под центром подразумевается центр между левой и правой стороной.
         * 
         * @param sideFaster скорость сантиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость сантиметров в секунду борта имеющего меньшую скорость движения
         * @return радиус разворота в милиметрах
         */
        uint16_t radiusTurnCenter(uint8_t sideFaster, uint8_t sideSlow)
        {
            return (sideFaster + sideSlow) / (sideFaster - sideSlow) * (BODY_WIDTH / 2);
        }

        /**
         * Угловая скорость. Скорость движения траспорта в повороте.
         * 
         * @param sideFaster скорость сантиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость сантиметров в секунду борта имеющего меньшую скорость движения
         * @return угловая скорость в сантиметрах в секунду
         */
        uint8_t cornerSpeed(uint8_t sideFaster, uint8_t sideSlow)
        {
            return (sideFaster + sideSlow) / 2;
        }

        /** 
         * Получение окружности из радиуса. 
         * 
         * @param radius радиус окружности в милиметрах
         * @return окружность в милиметрах
         */
        uint16_t circumference(uint16_t radius)
        {
            return (radius / 2) * 2 * 3.14;
        }

        /**
         * Расстояние окружности, которое необходимо преодолеть для поворота на указанное количество градусов.
         * 
         * @param circumference длина окружности в милиметрах
         * @param degree количество градусов, на которое необходимо повернуть
         * @return расстояние в милиметрах
         */
        uint16_t distanceInDegrees(uint16_t circumference, uint16_t degree)
        {
            return circumference / 360 * degree;
        }

        /**
         * Время необходимое для поворота на указанное количество градусов.
         * 
         * @param degree градусы, на которые необходимо развернуть транспорт
         * @param sideFaster скорость сантиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость сантиметров в секунду борта имеющего меньшую скорость движения
         * @return время для поворота в милисекундах
         */
        uint16_t timeForTurn(uint16_t degree, uint8_t sideFaster, uint8_t sideSlow)
        {
            uint8_t angleSpeed = cornerSpeed(sideFaster, sideSlow); // 45cm
            uint16_t radiusOfTurn = radiusTurnCenter(sideFaster, sideSlow); // 90mm
            uint16_t currentCircumference = circumference(radiusOfTurn); // 282mm
            uint16_t currentDistanceInDegrees = distanceInDegrees(currentCircumference, degree); // 70mm

            return currentDistanceInDegrees / angleSpeed * 1000;
        }
};