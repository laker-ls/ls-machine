#include <Arduino.h>
#include "Characteristics.h"
#include "sensors/Laser.h"
#include "sensors/Ultrasound.h"

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
         * @param distanceFront расстояние спереди до препятствия в сантиметрах.
         * @param distanceLeft расстояние слева до препятствия в сантиметрах
         * @param distanceRight расстояние справа до препятствия в сантиметрах
         */
        void main()
        {
            uint16_t* barrierFront = LaserObject.distanceWithAngle();

            if (barrierFront[0] < DISTANCE_CRITICAL) {
                goLeftInPlace(90 - barrierFront[1]);
            } else if (barrierFront[0] < DISTANCE_SMALL) {
                goRightInPlace(90 + barrierFront[1]);
            } else if (barrierFront[0] < DISTANCE_NORMAL) {
                goFront(SPEED_NORMAL);
            } else if (barrierFront[0] < DISTANCE_LARGE) {
                goFront(SPEED_LARGE);
            } else {
                goFront(SPEED_MAXIMUM);
            }
        }

    private:

        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;
        const uint16_t DISTANCE_CRITICAL = 20, DISTANCE_SMALL = 40, DISTANCE_NORMAL = 100, DISTANCE_LARGE = 160;
        const uint8_t SPEED_SMALL = 60, SPEED_NORMAL = 80, SPEED_LARGE = 100, SPEED_MAXIMUM = 120; // напряжение 12В, 212 pwm = 8 вольт

        Laser LaserObject;
        Ultrasound UltrasoundFront;
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

        /**
         * Определение ближайшего препятствия перед собой с помощью двух лазерных датчиков и одного ультразвука.
         * @return [0] - расстояние в сантиметрах, [1] - угол препятствия, где отрицательное значение означает, что правый угол дальше левого.
         */
        uint16_t* barrierFront()
        {
            uint16_t ultraDistance = UltrasoundFront.distance();
            uint16_t* laserDistance = LaserObject.distanceWithAngle();
            uint16_t* result = new uint16_t[2];

            if (ultraDistance > laserDistance[0] && ultraDistance > laserDistance[1]) {
                result[0] = ultraDistance;
                result[1] = 0;
            } else if (laserDistance[0] > ultraDistance && laserDistance[0] > laserDistance[1]) {
                result[0] = laserDistance[0];
                result[1] = laserDistance[2];
            } else {
                result[0] = laserDistance[1];
                result[1] = laserDistance[2];
            }

            return result;
        }
};