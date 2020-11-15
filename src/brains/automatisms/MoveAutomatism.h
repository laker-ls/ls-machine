#pragma once

#include "pinManagment/MotorDriverLN298N.h"

/**
 * Всё связанное с работой двигателей.
 */
class MoveAutomatism
{
    public:
        void init();

        void setParamsForMove(uint8_t move, uint8_t turn, uint8_t speed);

        /** Движение с плавным изменением скорости. Использовать в прерываниях. */
        void smoothMove();

    private:
        const uint8_t MINIMAL_SPEED = 40;
        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;

        MotorDriverLN298N MotorDriverLN298NObject;

        bool isMoveOfChange;

        uint8_t move;
        uint8_t turn;
        uint8_t needSpeed;
        
        uint8_t movePrev;
        uint8_t turnPrev;
        uint8_t currentSpeed;
        
        void setPins();
        void setInitialProperties();

        void setPreviousData();
        void changeSpeed();
        void moving();

        uint8_t speedLower();
};
