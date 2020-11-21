#include "VisionAutomatism.h"

void VisionAutomatism::init()
{
    this->setPinLaserSenses();
    this->setPinUltrasoundSenses();
}

void VisionAutomatism::setPinLaserSenses()
{
    LaserSenseLeft.init(LASER_LEFT);
    LaserSenseRight.init(LASER_RIGHT);
}

void VisionAutomatism::setPinUltrasoundSenses()
{
    UltrasoundSenseFrontLeft.setPins(ULTRASOUND_FRONT_LEFT);
    UltrasoundSenseFrontRight.setPins(ULTRASOUND_FRONT_RIGHT);
    UltrasoundSenseLeft.setPins(ULTRASOUND_LEFT);
    UltrasoundSenseRight.setPins(ULTRASOUND_RIGHT);
}

uint16_t VisionAutomatism::barrierFront()
{
    uint16_t distanceLaser = this->distanceOfLaserNearestFront();
    uint16_t distanceUltrasound = this->distanceOfUltrasoundNearestFront();

    return nearestDistance(distanceLaser, distanceUltrasound);
}

uint16_t VisionAutomatism::barrierLeft()
{
    return UltrasoundSenseLeft.distanceInCm();
}

uint16_t VisionAutomatism::barrierRight()
{
    return UltrasoundSenseRight.distanceInCm();
}

uint16_t VisionAutomatism::distanceOfLaserNearestFront()
{
    uint16_t distanceLeft = LaserSenseLeft.distanceInCm();
    uint16_t distanceRight = LaserSenseRight.distanceInCm();

    return this->nearestDistance(distanceLeft, distanceRight);
}

uint16_t VisionAutomatism::distanceOfUltrasoundNearestFront()
{
    uint16_t distanceFrontLeft = UltrasoundSenseFrontLeft.distanceInCm();
    uint16_t distanceFrontRight = UltrasoundSenseFrontRight.distanceInCm();

    return this->nearestDistance(distanceFrontLeft, distanceFrontRight);
}

uint16_t VisionAutomatism::nearestDistance(uint16_t first, uint16_t second)
{
    uint16_t result = first;

    if (second < first) {
        result = second;
    }

    return result;
}