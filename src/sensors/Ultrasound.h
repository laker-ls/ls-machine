#pragma once

/**
 * Работа с ультразвуковым датчиком расстояния HC-SR04.
 */
class Ultrasound
{
    private:
        uint8_t trig;
        uint8_t echo;

    public:
        /**
         * Назначение пинов для датчика расстояния.
         * 
         * @param eye массив, где первый элемент trig, второй echo
         */
        void setPin(const uint8_t *eye);

        void getPin();

        /**
         * @return расстояние в сантиметрах с ограничением на максимальное расстояние в 400см.
         */
        uint16_t distanceInCm();
};
