#pragma once

#include <Arduino.h>
#include "physicalParameters/pinsParameters.h"
#include "pinManagment/Speaker.h"

class SpeakerAutomatism
{
    public:
        void init();
        void wokeUp();

    private:
        Speaker SpeakerObject;
};