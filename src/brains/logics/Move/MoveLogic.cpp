#include "MoveLogic.h"

void MoveLogic::init()
{
    VisionAutomatismObject.init();
    ChoiceTurnObject.direction = DIRECTION_RIGHT;
    MoveAutomatismObject.init();
}

void MoveLogic::main()
{
    uint16_t barrierFrontLeft = VisionAutomatismObject.barrierFrontLeft();
    uint16_t barrierFrontRight = VisionAutomatismObject.barrierFrontRight();
    uint16_t barrierFront = VisionAutomatismObject.barrierFront(barrierFrontLeft, barrierFrontRight);

    uint16_t barrierLeft = VisionAutomatismObject.barrierLeft();
    uint16_t barrierRight = VisionAutomatismObject.barrierRight();

    uint8_t directionMove = this->choiceMove(barrierFront);
    uint8_t speed = this->choiceSpeed(barrierFront);
    uint8_t speedLower = this->speedLower(barrierFront);

    ChoiceTurnObject.calculate(barrierFrontLeft, barrierFrontRight, barrierFront, barrierLeft, barrierRight);

    MoveAutomatismObject.moving(directionMove, ChoiceTurnObject.direction, speed, speedLower);
}

uint8_t MoveLogic::choiceMove(uint16_t frontDistance)
{
    const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;

    uint8_t result = MOVE_FORWARD;
    if (frontDistance < DISTANCE_CRITICAL) {
        result = MOVE_IN_PLACE;
    }
    return result;
}

uint8_t MoveLogic::choiceSpeed(uint16_t frontDistance)
{
    const uint8_t SPEED_CRITICAL = 60;
    const uint16_t MAX_DISTANCE = 120;
    if (frontDistance > MAX_DISTANCE) {
        frontDistance = MAX_DISTANCE;
    }
    return ((frontDistance / 1.8) + SPEED_CRITICAL);
}

uint8_t MoveLogic::speedLower(uint16_t frontDistance)
{
    const uint8_t DIFFERENCE_TO_TURN = 60;

    uint8_t speed = this->choiceSpeed(frontDistance);
    return (speed - DIFFERENCE_TO_TURN);
}
