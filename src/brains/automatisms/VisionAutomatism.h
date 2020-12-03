#pragma once

#include "physicalParameters/pinsParameters.h"
#include "brains/senseOrgans/vision/LaserSense.h"
#include "brains/senseOrgans/vision/UltrasoundSense.h"

/**
 * Зрение робота. Обработка данных полученных от различных датчиков расстояния.
 */
class VisionAutomatism
{
    public:
        void init();
        uint16_t barrierFront(uint16_t barrierFrontLeft, uint16_t barrierFrontRight);
        uint16_t barrierFrontLeft();
        uint16_t barrierFrontRight();

        uint16_t barrierLeft();
        uint16_t barrierRight();

    private:
        LaserSense LaserSenseLeft;
        LaserSense LaserSenseRight;
        UltrasoundSense UltrasoundSenseFrontLeft;
        UltrasoundSense UltrasoundSenseFrontRight;
        UltrasoundSense UltrasoundSenseLeft;
        UltrasoundSense UltrasoundSenseRight;

        void setPinLaserSenses();
        void setPinUltrasoundSenses();
        uint16_t distanceOfUltrasoundNearestFront();
        uint16_t nearestDistance(uint16_t first, uint16_t second);
};