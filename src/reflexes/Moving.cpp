#include "main.h"

void Moving::main()
{
    uint16_t barrierFront = VisionObject.barrierFront();

    if (barrierFront < DISTANCE_CRITICAL) {
        // goLeftInPlace(90 - barrierFront[1]);
        goLeftInPlace(20);
    } else if (barrierFront < DISTANCE_SMALL) {
        goFront(SPEED_SMALL);
    } else if (barrierFront < DISTANCE_NORMAL) {
        goFront(SPEED_NORMAL);
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

void Moving::goLeftInPlace(uint16_t angleRotation)
{
    MovementObject.turn(MOVE_IN_PLACE, DIRECTION_LEFT, SPEED_NORMAL, angleRotation);
}

void Moving::goRightInPlace(uint16_t angleRotation)
{
    MovementObject.turn(MOVE_IN_PLACE, DIRECTION_RIGHT, SPEED_NORMAL, angleRotation);
}