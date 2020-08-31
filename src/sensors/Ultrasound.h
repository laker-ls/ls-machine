#pragma once
#include <Arduino.h>

/**
 * Работа с ультразвуковым датчиком расстояния HC-SR04.
 */
class Ultrasound
{
    public:
        uint8_t trig;
        uint8_t echo;

        /**
         * Назначение пинов для датчика расстояния.
         * 
         * @param eye массив, где первый элемент trig, второй echo
         */
        void setPin(const uint8_t *eye)
        {
            trig = eye[0];
            echo = eye[1];

            pinMode (trig, OUTPUT);
            pinMode (echo, INPUT);
        }

        /**
         * Растояние до препятствия, обработанное от погрешностей.
         * 
         * @return расстояние в сантиметрах
         */
        uint16_t distance()
        {
            uint16_t duration, cm;

            digitalWrite(trig, LOW);
            delayMicroseconds(2);
            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);
            
            duration = pulseIn(echo, HIGH, 23200); // 23200 = 400cm.
            if (duration == 0) {
                cm = 999;
            } else {
                cm = (duration / 2) / 29;
            }

            return cm;
        }
};
