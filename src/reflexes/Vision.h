#include <Arduino.h>
#include "Characteristics.h"
#include "sensors/Laser.h"
#include "sensors/Ultrasound.h"

/**
 * Зрение робота. Обработка данных полученных от различных датчиков расстояния.
 */
class Vision
{
    public:
        /**
         * Определение ближайшего препятствия перед собой с помощью двух лазерных датчиков и двух ультразвуковых.
         * @return Расстояние в сантиметрах.
         */
        uint16_t barrierFront(Laser LaserObject)
        {
            return distanceOfLaserNearestBarrierFront(LaserObject);
        }

    private:
        /**
         * @return Расстояние от лазерных датчиков до ближайшего препятствия.
         */
        uint16_t distanceOfLaserNearestBarrierFront(Laser LaserObject)
        {
            uint16_t distanceLeft = LaserObject.distanceLeftInCm();
            uint16_t distanceRight = LaserObject.distanceRightInCm();
            uint16_t result = distanceRight;

            Serial.begin(9600);
            Serial.println("left");
            Serial.println(distanceLeft);
            Serial.println("right");
            Serial.println(distanceRight);

            if (distanceLeft < distanceRight) {
                result = distanceLeft;
            }

            return result;
        }

        // uint16_t distanceOfUltrasound()
        // {
        //     uint16_t ultraDistance = UltrasoundFront.distance();
        //     int16_t* laserDistance = LaserObject.distanceWithAngle();
        //     int16_t* result = new int16_t[2];

        //     if (ultraDistance > laserDistance[0] && ultraDistance > laserDistance[1]) {
        //         result[0] = ultraDistance;
        //         result[1] = 0;
        //     } else if (laserDistance[0] > ultraDistance && laserDistance[0] > laserDistance[1]) {
        //         result[0] = laserDistance[0];
        //         result[1] = laserDistance[2];
        //     } else {
        //         result[0] = laserDistance[1];
        //         result[1] = laserDistance[2];
        //     }

        //     return result;
        // }
};