#include <Arduino.h>
#include "Characteristics.h"
#include "reflexes/Vision.h"

/**
 * Принятие решения как двигаться исходя из показаний датчиков.
 */
class Moving
{
    public:
        Moving()
        {
            Laser LaserObject;
            Ultrasound UltrasoundFront;
            Movement MovementObject;

            UltrasoundFront.setPin(ULTRASOUND_FRONT);        
        }

        /**
         * Главная функция управляющая движением.
         */
        void main(Laser LaserObject, Vision VisionObject)
        {
            uint16_t barrierFront = VisionObject.barrierFront(LaserObject);

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

    private:
        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;
        const uint16_t DISTANCE_CRITICAL = 30, DISTANCE_SMALL = 40, DISTANCE_NORMAL = 100, DISTANCE_LARGE = 160;
        const uint8_t SPEED_SMALL = 60, SPEED_NORMAL = 80, SPEED_LARGE = 100, SPEED_MAXIMUM = 120;

        Movement MovementObject;

        /**
         * Движение вперед.
         */
        void goFront(uint8_t speed)
        {
            MovementObject.turn(MOVE_FORWARD, DIRECTION_NO_TURN, speed, 0);
        }

        /**
         * Движение влево.
         */
        void goLeftInPlace(uint16_t angleRotation)
        {
            MovementObject.turn(MOVE_IN_PLACE, DIRECTION_LEFT, SPEED_NORMAL, angleRotation);
        }

        /**
         * Движение вправо.
         */
        void goRightInPlace(uint16_t angleRotation)
        {
            MovementObject.turn(MOVE_IN_PLACE, DIRECTION_RIGHT, SPEED_NORMAL, angleRotation);
        }
};