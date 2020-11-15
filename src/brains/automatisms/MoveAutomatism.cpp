#include "main.h"

void MoveAutomatism::init()
{
    MotorDriverLN298NObject.setPins();
    this->setInitialProperties();
}

void MoveAutomatism::setInitialProperties()
{
    this->movePrev = 0;
    this->turnPrev = 0;
    this->currentSpeed = 0;
}

void MoveAutomatism::setParamsForMove(uint8_t move, uint8_t turn, uint8_t speed)
{
    this->move = move;
    this->turn = turn;
    
    if (move != this->movePrev) {
        this->needSpeed = this->MINIMAL_SPEED;
    } else {
       this->needSpeed = speed;
    }
}

ISR(TIMER1)
{
    MoveAutomatismObject.smoothMove();
}

void MoveAutomatism::smoothMove()
{
    this->setPreviousData();
    this->changeSpeed();
    this->moving();
}

void MoveAutomatism::setPreviousData()
{
    if (this->currentSpeed <= this->MINIMAL_SPEED) {
        this->movePrev = this->move;
        this->turnPrev = this->turn;
    }
}

void MoveAutomatism::changeSpeed()
{
    if (this->currentSpeed < this->needSpeed && this->currentSpeed < 250) {
        this->currentSpeed += 4;
    } else if (this->currentSpeed > this->needSpeed && this->currentSpeed > this->MINIMAL_SPEED) {
        this->currentSpeed -= 4;
    }
}

void MoveAutomatism::moving() 
{            
    if (this->movePrev == 0) { // движение вперед
        switch (this->turnPrev) {
            case 0:
                MotorDriverLN298NObject.moveForward(this->currentSpeed);
                break;
            case 1:
                MotorDriverLN298NObject.moveLeft(this->currentSpeed, this->speedLower());
                break;
            case 2:
                MotorDriverLN298NObject.moveRight(this->currentSpeed, this->speedLower());
                break;
        }
    } else if (this->movePrev == 1) { // движение на месте
        switch (this->turnPrev) {
            case 0:
                MotorDriverLN298NObject.moveInPlaceStop();
                break;
            case 1:
                MotorDriverLN298NObject.moveInPlaceLeft(this->currentSpeed);
                break;
            case 2:
                MotorDriverLN298NObject.moveInPlaceRight(this->currentSpeed);
                break;
        }
    }
}

uint8_t MoveAutomatism::speedLower()
{
    return (this->currentSpeed / 3);
}
