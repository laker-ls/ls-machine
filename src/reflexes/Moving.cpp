#include "main.h"

void Moving::main()
{
    uint16_t barrierFront = VisionObject.barrierFront();
    uint16_t barrierLeft = UltrasoundLeft.distanceInCm();
    uint16_t barrierRight = UltrasoundRight.distanceInCm();

    if (barrierFront < DISTANCE_CRITICAL) {
        if (barrierLeft < barrierRight) {
            goRightInPlace(20);
        } else {
            goLeftInPlace(20);
        }
    } else if (barrierFront < DISTANCE_SMALL) {
        if (barrierLeft < barrierRight) {
            goRight(SPEED_LARGE, 20);
        } else {
            goLeft(SPEED_LARGE, 20);
        }
    } else if (barrierFront < DISTANCE_NORMAL) {
        if (barrierLeft < barrierRight) {
            goRight(SPEED_MAXIMUM, 20);
        } else {
            goLeft(SPEED_MAXIMUM, 20);
        }
    } else if (barrierFront < DISTANCE_LARGE) {
        goFront(SPEED_LARGE);
    } else {
        goFront(SPEED_MAXIMUM);
    }
}

void Moving::goFront(uint8_t speed)
{
    MovementObject.turn(MOVE_FORWARD, DIRECTION_NO_TURN, speed, 0);
}

void Moving::goLeft(uint8_t speed, uint16_t angleRotation)
{
    MovementObject.turn(MOVE_FORWARD, DIRECTION_LEFT, speed, angleRotation);
}

void Moving::goRight(uint8_t speed, uint16_t angleRotation)
{
    MovementObject.turn(MOVE_FORWARD, DIRECTION_RIGHT, speed, angleRotation);
}

void Moving::goLeftInPlace(uint16_t angleRotation)
{
    MovementObject.turn(MOVE_IN_PLACE, DIRECTION_LEFT, SPEED_SMALL, angleRotation);
}

void Moving::goRightInPlace(uint16_t angleRotation)
{
    MovementObject.turn(MOVE_IN_PLACE, DIRECTION_RIGHT, SPEED_SMALL, angleRotation);
}