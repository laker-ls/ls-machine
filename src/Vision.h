#pragma once
#include <Arduino.h>

/**
 * Работа с датчиком расстояния HC-SR04.
 */
class Vision
{
    public:
        /**
         * Растояние до препятствия, обработанное от погрешностей.
         * 
         * @param eye массив, где первый элемент trig, второй echo
         * @return расстояние в сантиметрах
         */
        uint16_t distance(const uint8_t *eye)
        {
            /** Чем выше количество итераций, тем более точные показания, но необходимо большее количество времени для замера. */
            const uint8_t ITERATION_OF_DISTANCE = 3;

            uint16_t *rawDatas, result;
            uint16_t *datas = 0;

            for(uint8_t i = 0; i < ITERATION_OF_DISTANCE; i++) {
                for (uint8_t d = 0; d < 3; d++) {
                    rawDatas[d] = rawDistance(eye);
                }
                datas[i] = averageOfThree(rawDatas[0], rawDatas[1], rawDatas[2]);
            }
            result = arithmeticalMean(datas, ITERATION_OF_DISTANCE);

            return result;
        }

    private:
        /**
         * Замер расстояния до препятствия.
         * 
         * @param eye массив, где первый элемент trig, второй echo
         * @return расстояние в сантиметрах
         */
        uint16_t rawDistance(const uint8_t *eye) 
        {
            uint16_t duration, cm;

            digitalWrite(eye[0], HIGH);
            delayMicroseconds(10);
            digitalWrite(eye[0], LOW);

            duration = pulseIn(eye[1], HIGH, 23200); // 23200 = 400cm.
            if (duration == 0) {
                cm = 999;
            } else {
                cm = (duration / 2) / 29;
            }

            return cm;
        }

        /**
         * Медианный фильтр по трем значениям. Отсеивание сильно отличающиеся значения.
         */
        uint16_t averageOfThree(uint16_t a, uint16_t b, uint16_t c)
        {
            uint16_t average;

            if (a <= b && a <= c) {
                average = (b <= c) ? b : c;
            } else if (b <= a && b <= c) {
                average = (a <= c) ? a : c;
            } else if (c <= a && c <= b) {
                average = (a <= b) ? a : b;
            } else {
                average = 0;
            }

            return average;
        }

        /**
         * Фильтр "Среднее арифметическое". Сглаживание полученных значений.
         */
        uint16_t arithmeticalMean(uint16_t *array, uint8_t length)
        {
            uint16_t average = 0;

            for (uint8_t i = 0; i < length; i++) {
                average += array[i];
            }
            average = (average / length);

            return average;
        }
};
