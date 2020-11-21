#include <Arduino.h>
#include "physicalParameters/pinsParameters.h"
#include "registers/Timer3.h"

class MotorDriverLN298N
{
    public:
        void init();
        
        void moveForward(uint8_t speed);
        void moveLeft(uint8_t speed, uint8_t speedLower);
        void moveRight(uint8_t speed, uint8_t speedLower);

        void moveInPlaceStop();
        void moveInPlaceLeft(uint8_t speed);
        void moveInPlaceRight(uint8_t speed);

    private:
        Timer3 Timer3Object; 

        void setPins();
        void settingTimer3();
};
