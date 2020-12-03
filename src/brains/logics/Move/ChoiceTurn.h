#pragma once
#include <Arduino.h>

class ChoiceTurn
{
    public:
        uint8_t direction;

        void calculate(uint16_t frontLeftDistance, uint16_t frontRightDistance, uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance);   
    private:
        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint16_t DISTANCE_LARGE = 110, DISTANCE_CRITICAL = 40;

        uint16_t frontLeftDistance, frontRightDistance, frontDistance, leftDistance, rightDistance;
        bool isBarrierAvoid, isLateralDifferenceGood, isDistanceLarge, isDistanceCritical;

        void setProperties(uint16_t frontLeftDistance, uint16_t frontRightDistance, uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance);
        void setChecks();
        bool calculateLateralDifferenceGood();

        void directionNotTurn();
        void directionTurn();
};