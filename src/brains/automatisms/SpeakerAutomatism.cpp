#include "SpeakerAutomatism.h"

void SpeakerAutomatism::init()
{
    SpeakerObject.setPin();
}

void SpeakerAutomatism::wokeUp()
{
    tone(SPEAKER, 200);
    delay(200);
    tone(SPEAKER, 100);
    delay(100);
    tone(SPEAKER, 300);
    delay(100);
    tone(SPEAKER, 600);
    delay(200);
    noTone(SPEAKER);
}
