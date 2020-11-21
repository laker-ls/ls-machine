#include "MoveAutomatism.h"

void MoveAutomatism::init()
{
    MotorDriverLN298NObject.init();
}

void MoveAutomatism::moving(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint8_t speedLower) 
{            
    if (directionMove == 0) { // движение вперед
        switch (directionTurn) {
            case 0:
                MotorDriverLN298NObject.moveForward(speed);
                break;
            case 1:
                MotorDriverLN298NObject.moveLeft(speed, speedLower);
                break;
            case 2:
                MotorDriverLN298NObject.moveRight(speed, speedLower);
                break;
        }
    } else if (directionMove == 1) { // движение на месте
        switch (directionTurn) {
            case 0:
                MotorDriverLN298NObject.moveInPlaceStop();
                break;
            case 1:
                MotorDriverLN298NObject.moveInPlaceLeft(speed);
                break;
            case 2:
                MotorDriverLN298NObject.moveInPlaceRight(speed);
                break;
        }
    }
}
