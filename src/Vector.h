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
         * Обороты в минуту.
         */
        float rpm(uint8_t pwm)
        {
            const float VOLT_IN_ONE_PWM = (MOTOR_VOLTAGE / 255);
            const float rpmInOneVolt = 47.5;
            float volt = pwm * VOLT_IN_ONE_PWM;
            
            return volt * rpmInOneVolt;
        }

        /**
         * Расстояние в миллиметрах за секунду.
         */
        float millimetersPerSecond(uint8_t pwm)
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
        float radiusTurnSlowSide(float sideFaster, float sideSlow)
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
        float radiusTurnFasterSide(float sideFaster, float sideSlow)
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
        float radiusTurnCenter(float sideFaster, float sideSlow)
        {
            return (sideFaster + sideSlow) / (sideFaster - sideSlow) * (BODY_WIDTH / 2);
        }

        /**
         * Угловая скорость. Скорость движения траспорта в повороте.
         * 
         * @param sideFaster скорость в миллиметрах в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость в миллиметрах в секунду борта имеющего меньшую скорость движения
         * @return угловая скорость в миллиметрах в секунду
         */
        float cornerSpeed(float sideFaster, float sideSlow)
        {
            return (sideFaster + sideSlow) / 2;
        }

        /** 
         * Получение окружности из радиуса. 
         * 
         * @param radius радиус окружности в миллиметрах
         * @return окружность в миллиметрах
         */
        float circumference(float radius)
        {
            return radius * 3.14;
        }

        /**
         * Расстояние окружности, которое необходимо преодолеть для поворота на указанное количество градусов.
         * 
         * @param circumference длина окружности в милиметрах
         * @param degree количество градусов, на которое необходимо повернуть
         * @return расстояние в милиметрах
         */
        float distanceInDegrees(float circumference, uint16_t degree)
        {
            return circumference / 360 * degree;
        }

        /**
         * Время необходимое для поворота на указанное количество градусов.
         * 
         * @param degree градусы, на которые необходимо развернуть транспорт
         * @param sideFaster скорость миллиметров в секунду борта имеющего большую скорость движения
         * @param sideSlow скорость миллиметров в секунду борта имеющего меньшую скорость движения
         * @return время для поворота в милисекундах
         */
        float timeForTurn(uint16_t degree, float sideFaster, float sideSlow)
        {
            // degree 90
            // sidefaster - 523mm
            float angleSpeed = cornerSpeed(sideFaster, sideSlow); // 261mm
            float radiusOfTurn = radiusTurnCenter(sideFaster, sideSlow); // 90mm
            float currentCircumference = circumference(radiusOfTurn); // 282mm
            float currentDistanceInDegrees = distanceInDegrees(currentCircumference, degree); // 204mm
            // return 778

            return currentDistanceInDegrees / angleSpeed * 1000;
        }
};