#pragma once
#include <Arduino.h>

/**
 * Точность таймера под вопросом. 
 * С помощью millis() и Serial.print() погрешность 160мс при интервале в 4000мс
 * Чем меньше интервал замыкания, тем меньше погрешность.
 */
class Timer1
{
    public:
        #define TIMER1 TIMER1_COMPA_vect

    private:
        /** 
         * 1024 - рабочий множитель до 4000мс. 
         * 256, 64, 8, 1 - не корректно работающие множители. 
         * 0 - остановить таймер. 
         */
        const uint32_t DIVIDER = 1024;

        /** Частота процессора в МГц. */
        const uint32_t CLOCK_FREQUENCY = 16;

    public:
        /** 
         * Периодичность прерываний. 
         * @param milliseconds частота прерываний в милисекундах.
         */
        void setInterval(uint32_t milliseconds);

    private:
        /** Расчёт значения для регистра совпадения. */
        uint32_t intervalCalculate(uint32_t milliseconds);

        /** Установка регистра - делитель счётчика */
        void setDividerRegister();
};