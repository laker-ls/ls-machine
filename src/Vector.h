#pragma once
#include <Arduino.h>

/**
 * Методы для рассчетов векторных значений.
 */
class Vector
{
    protected:
        const uint8_t DIAMETER_WHEEL; // в милиметрах
        const uint16_t RPM; // обороты в минуту на максимальной скорости (55 оборотов за 1 вольт)

        /** 
         * Рассчитываем скорость второй пары колес исходя из текущей скорости и угла на который необходимо повернуть. 
         * @param currentSpeed скорость с которой движется объект в PWM
         * @param angleRotation угол, на который необходимо повернуть
         */
        uint8_t pwmForTurning(uint8_t currentSpeed, uint16_t angleRotation)
        {
            uint8_t speedForAngle;

            speedForAngle =  1;
        }

        /** Скорость движения (сантиметров в секунду) */
        uint8_t centimetersPerSecond()
        {
            return RPM / 60 * circumferenceWheel();
        }

        /** Расчет радиуса поворота */
        uint16_t radiusTurn()
        {
            uint8_t v2 = 1, v1 = 0.5, b = 120;
            uint16_t result;

            result = (v2 + v1) / (v2 - v1) * (b / 2);

            return result;
        }
    private:
        /** Окружность колеса в милиметрах. */
        uint16_t circumferenceWheel()
        {
            return (DIAMETER_WHEEL / 2) * 2 * 3.14;
        }
};