#pragma once

/**
 * Принятие решения как двигаться исходя из показаний датчиков.
 */
class Moving
{
    public:
        /**
         * Главная функция управляющая движением.
         */
        void main();

    private:
        const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
        const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;
        const uint16_t DISTANCE_CRITICAL = 30, DISTANCE_SMALL = 40, DISTANCE_NORMAL = 100, DISTANCE_LARGE = 160;
        const uint8_t SPEED_SMALL = 60, SPEED_NORMAL = 80, SPEED_LARGE = 100, SPEED_MAXIMUM = 120;

        void goFront(uint8_t speed);
        void goLeftInPlace(uint16_t angleRotation);
        void goRightInPlace(uint16_t angleRotation);
};