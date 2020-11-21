#pragma once
#include <Arduino.h>

class ChoiceTurn
{
    public:
        uint8_t direction;

        void calculate(uint16_t forwardDistance, uint16_t leftDistance, uint16_t rightDistance);   
    private:
        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint16_t DISTANCE_LARGE = 110, DISTANCE_CRITICAL = 40;

        uint16_t frontDistance, leftDistance, rightDistance;

        void setProperties(uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance);

        void directionNotTurn();
        void directionTurn();

        bool isLaterDifferenceGood();
        bool isDistanceLarge();
        bool isDistanceCritical();
};