#include "main.h"

void MoveLogic::main()
{
    uint16_t barrierFront = VisionAutomatismObject.barrierFront();
    uint16_t barrierLeft = VisionAutomatismObject.barrierLeft();
    uint16_t barrierRight = VisionAutomatismObject.barrierRight();

    if (barrierFront < this->DISTANCE_CRITICAL) {
        if (barrierLeft < barrierRight) {
            goRightInPlace(this->SPEED_SMALL);
        } else {
            goLeftInPlace(this->SPEED_SMALL);
        }
    } else if (barrierFront < this->DISTANCE_SMALL) {
        if (barrierLeft < barrierRight) {
            goRight(this->SPEED_LARGE);
        } else {
            goLeft(this->SPEED_LARGE);
        }
    } else if (barrierFront < this->DISTANCE_NORMAL) {
        if (barrierLeft < barrierRight) {
            goRight(this->SPEED_MAXIMUM);
        } else {
            goLeft(this->SPEED_MAXIMUM);
        }
    } else if (barrierFront < this->DISTANCE_LARGE) {
        goFront(this->SPEED_LARGE);
    } else {
        goFront(this->SPEED_MAXIMUM);
    }
}

void MoveLogic::goFront(uint8_t speed)
{
    MoveAutomatismObject.setParamsForMove(MOVE_FORWARD, DIRECTION_NO_TURN, speed);
}

void MoveLogic::goLeft(uint8_t speed)
{
    MoveAutomatismObject.setParamsForMove(MOVE_FORWARD, DIRECTION_LEFT, speed);
}

void MoveLogic::goRight(uint8_t speed)
{
    MoveAutomatismObject.setParamsForMove(MOVE_FORWARD, DIRECTION_RIGHT, speed);
}

void MoveLogic::goLeftInPlace(uint8_t speed)
{
    MoveAutomatismObject.setParamsForMove(MOVE_IN_PLACE, DIRECTION_LEFT, SPEED_SMALL);
}

void MoveLogic::goRightInPlace(uint8_t speed)
{
    MoveAutomatismObject.setParamsForMove(MOVE_IN_PLACE, DIRECTION_RIGHT, SPEED_SMALL);
}
