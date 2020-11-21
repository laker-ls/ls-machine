#include "ChoiceTurn.h"

void ChoiceTurn::calculate(uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance)
{
    this->setProperties(frontDistance, leftDistance, rightDistance);

    if (this->isDistanceLarge()) {
        this->directionNotTurn();
    } else if (this->isDistanceCritical() || this->isLaterDifferenceGood()) {
        this->directionTurn();
    }
}

void ChoiceTurn::setProperties(uint16_t frontDistance, uint16_t leftDistance, uint16_t rightDistance)
{
    this->frontDistance = frontDistance;
    this->leftDistance = leftDistance;
    this->rightDistance = rightDistance;
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

bool ChoiceTurn::isLaterDifferenceGood()
{
    const uint8_t distanceDifferenceMinimal = ((this->frontDistance / 1.8) + 40);

    bool result = false;
    uint16_t distanceDifference = (this->leftDistance - this->rightDistance);
    if (distanceDifference > distanceDifferenceMinimal) {
        result = true;
    }
    return result;
}

bool ChoiceTurn::isDistanceLarge()
{
    bool result = false;
    if (this->frontDistance >= this->DISTANCE_LARGE) {
        result = true;
    }
    return result;
}

bool ChoiceTurn::isDistanceCritical()
{
    bool result = false;
    if (this->frontDistance <= this->DISTANCE_CRITICAL) {
        result = true;
    }
    return result;
}