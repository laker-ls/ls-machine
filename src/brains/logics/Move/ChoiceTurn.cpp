#include "ChoiceTurn.h"

void ChoiceTurn::calculate(uint16_t frontLeftDistance, uint16_t frontRightDistance, uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance)
{
    this->setProperties(frontLeftDistance, frontRightDistance, frontDistance, leftDistance, rightDistance);
    this->setChecks();

    if (this->isDistanceLarge) {
        this->directionNotTurn();
    } else if () {
        
    } else if ((this->isDistanceCritical && this->isBarrierAvoid) || (!this->isDistanceCritical && this->isLateralDifferenceGood)) {
        this->directionTurn();
    }
}

void ChoiceTurn::setProperties(uint16_t frontLeftDistance, uint16_t frontRightDistance, uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance)
{
    this->frontLeftDistance = frontLeftDistance;
    this->frontRightDistance = frontRightDistance;
    this->frontDistance = frontDistance;
    this->leftDistance = leftDistance;
    this->rightDistance = rightDistance;
}

void ChoiceTurn::setChecks()
{
    this->isDistanceLarge = (this->frontDistance >= this->DISTANCE_LARGE);
    this->isDistanceCritical = (this->frontDistance <= this->DISTANCE_CRITICAL);
    this->isBarrierAvoid = (this->direction != DIRECTION_NO_TURN);
    this->isLateralDifferenceGood = calculateLateralDifferenceGood();
}

bool ChoiceTurn::calculateLateralDifferenceGood()
{
    const uint8_t distanceDifferenceMinimal = ((this->frontDistance / 1.8) + 40);
    uint16_t distanceDifference = (this->leftDistance - this->rightDistance);

    bool result = false;
    if (distanceDifference > distanceDifferenceMinimal) {
        result = true;
    }
    return result;
}

void ChoiceTurn::directionNotTurn()
{
    this->direction = DIRECTION_NO_TURN;
}

void ChoiceTurn::directionTurn()
{
    if (this->leftDistance > this->rightDistance) {
        this->direction = DIRECTION_LEFT;
    } else {
        this->direction = DIRECTION_RIGHT;
    }
}
