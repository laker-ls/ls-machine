#pragma once

/**
 * Зрение робота. Обработка данных полученных от различных датчиков расстояния.
 */
class VisionAutomatism
{
    public:
        uint16_t barrierFront();
        uint16_t barrierLeft();
        uint16_t barrierRight();

    private:
        uint16_t distanceOfLaserNearestFront();
        uint16_t distanceOfUltrasoundNearestFront();
        uint16_t nearestDistance(uint16_t first, uint16_t second);

};