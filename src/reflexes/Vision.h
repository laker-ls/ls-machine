#pragma once

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
        uint16_t barrierFront();

    private:
        /**
         * @return Расстояние от лазерных датчиков до ближайшего препятствия.
         */
        uint16_t distanceOfLaserNearestFront();

        /**
         * @return Расстояние от ультразвуковых датчиков до ближайшего препятствия.
         */
        uint16_t distanceOfUltrasoundNearestFront();

        /**
         * @param first
         * @param second
         * @return Ближайшие показания из двух расстояний до объекта.
         */
        uint16_t nearestDistance(uint16_t first, uint16_t second);
};