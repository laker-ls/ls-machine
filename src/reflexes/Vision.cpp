#include "main.h"

uint16_t Vision::barrierFront()
{
    uint16_t distanceLaser = distanceOfLaserNearestFront();
    uint16_t distanceUltrasound = distanceOfUltrasoundNearestFront();

    return nearestDistance(distanceLaser, distanceUltrasound);
}

uint16_t Vision::distanceOfLaserNearestFront()
{
    uint16_t distanceLeft = LaserObject.distanceLeftInCm();
    uint16_t distanceRight = LaserObject.distanceRightInCm();

    return nearestDistance(distanceLeft, distanceRight);
}

uint16_t Vision::distanceOfUltrasoundNearestFront()
{
    uint16_t distanceFrontLeft = UltrasoundFrontLeft.distanceInCm();
    uint16_t distanceFrontRight = UltrasoundFrontRight.distanceInCm();

    return nearestDistance(distanceFrontLeft, distanceFrontRight);
}

uint16_t Vision::nearestDistance(uint16_t first, uint16_t second)
{
    uint16_t result = first;

    if (second < first) {
        result = second;
    }

    return result;
}