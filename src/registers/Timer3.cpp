#include "main.h"

void Timer3::setDividerRegister(uint16_t devider)
{
    TCCR3B = 0;
    switch (devider)
    {
        case 1024:
            // 101
            TCCR3B |= ((1 << CS30) | (1 << CS32));
            break;
        case 256:
            // 100
            TCCR3B |= (1 << CS32);
            break;
        case 64:
            // 011
            TCCR3B |= ((1 << CS30) | (1 << CS31));
            break;
        case 8:
            // 010
            TCCR3B |= (1 << CS31);
            break;
        case 1:
            // 001
            TCCR3B |= (1 << CS30);
            break;
    }
}