#pragma once

#include "pinManagment/MotorDriverLN298N.h"

/**
 * Всё связанное с работой двигателей.
 */
class MoveAutomatism
{
    public:
        void init();
        void moving(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint8_t speedLower);
    private:
        MotorDriverLN298N MotorDriverLN298NObject;
};
