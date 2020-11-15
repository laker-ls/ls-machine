#include "Timer1.h"

void Timer1::setInterval(uint32_t milliseconds)
{
    /** Обнуление регистра. */
    TCCR1B = 0;

    /** Регистр совпадения с необходимым значением для срабатывания. */
    OCR1A = this->intervalCalculate(milliseconds);

    /** СТС режим. Установка режима прерывания по совпадению. */
    TCCR1B |= (1 << WGM12); 

    setDividerRegister();

    /** Режим прерывания по совпадению. */
    TIMSK1 |= (1 << OCIE1A);
}

uint32_t Timer1::intervalCalculate(uint32_t milliseconds)
{
    uint32_t iterationsInMillisecond = (CLOCK_FREQUENCY * 1000000 / DIVIDER / 1000);
    return (milliseconds * iterationsInMillisecond);
}

void Timer1::setDividerRegister()
{
    switch (DIVIDER) {
        case 1024:
            TCCR1B |= ((1 << CS10) | (1 << CS12));
            break;
        case 256:
            TCCR1B |= (1 << CS12);
            break;
        case 64:
            TCCR1B |= ((1 << CS10) | (1 << CS11));
            break;
        case 8:
            TCCR1B |= (1 << CS11);
            break;
        case 1:
            TCCR1B |= (1 << CS10);
            break;
    }
}