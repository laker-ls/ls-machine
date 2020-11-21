#pragma once

#include "ChoiceTurn.h"
#include "brains/automatisms/VisionAutomatism.h"
#include "brains/automatisms/MoveAutomatism.h"

/**
 * Принятие решения как двигаться исходя из показаний датчиков.
 */
class MoveLogic
{
    public:
        void init();
        void main();

    private:
        const uint8_t DIRECTION_RIGHT = 2;
        const uint8_t DISTANCE_CRITICAL = 40;

        ChoiceTurn ChoiceTurnObject;
        VisionAutomatism VisionAutomatismObject;
        MoveAutomatism MoveAutomatismObject;

        uint8_t choiceMove(uint16_t frontDistance);
        uint8_t choiceSpeed(uint16_t frontDistance);
        uint8_t speedLower(uint16_t frontDistance);
};
