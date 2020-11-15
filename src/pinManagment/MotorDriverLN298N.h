#include <Arduino.h>
#include "physicalParameters/pinsParameters.h"

class MotorDriverLN298N
{
    public:
        void setPins();

        void moveForward(uint8_t speed);
        void moveLeft(uint8_t speed, uint8_t speedLower);
        void moveRight(uint8_t speed, uint8_t speedLower);

        void moveInPlaceStop();
        void moveInPlaceLeft(uint8_t speed);
        void moveInPlaceRight(uint8_t speed);
};
