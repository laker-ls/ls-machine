#pragma once

/**
 * Всё связанное с работой двигателей.
 */
class Movement
{
    public:
        void init();

        /**
         * Различные движения машины, путем установки ШИМ сигнала.
         * 
         * @param directionMove направление движения, 0 - вперед, 1 - на месте
         * @param directionTurn направление поворота, 0 - без поворотов, 1 - влево, 2 - вправо
         * @param speed скорость движения
         * @param angleRotation угол на который необходимо повернуть
         */
        void turn(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint16_t angleRotation);

        /**
         * Поворот на указанное количество градусов.
         * 
         * @param degree градусы, на которые необходимо развернуть транспорт
         * @param sideFaster скорость в PWM борта имеющего большую скорость движения
         * @param sideSlow скорость в PWM борта имеющего меньшую скорость движения
         */
        void delayTurn(uint16_t degree, uint8_t sideFaster, uint8_t sideSlow);
};