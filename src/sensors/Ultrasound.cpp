#include "main.h"

uint8_t trig;
uint8_t echo;

void Ultrasound::setPin(const uint8_t *eye)
{
    trig = eye[0];
    echo = eye[1];

    pinMode (trig, OUTPUT);
    pinMode (echo, INPUT);
}

uint16_t Ultrasound::distance()
{
    uint16_t duration, cm;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    duration = pulseIn(echo, HIGH, 23200); // 23200 = 400см.
    if (duration == 0) {
        cm = 999;
    } else {
        cm = (duration / 2) / 29;
    }

    return cm;
}
