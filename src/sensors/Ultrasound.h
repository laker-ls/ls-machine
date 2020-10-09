#pragma once

/**
 * Работа с ультразвуковым датчиком расстояния HC-SR04.
 */
class Ultrasound
{
    public:
        /**
         * Назначение пинов для датчика расстояния.
         * 
         * @param eye массив, где первый элемент trig, второй echo
         */
        void setPin(const uint8_t *eye);

    private:
        /**
         * @return расстояние в сантиметрах с ограничением на максимальное расстояние в 400см.
         */
        uint16_t distance();
};
