#pragma once
#include <Arduino.h>

/**
 * Всё связанное с работой двигателей.
 */
class Movement 
{
    public:
        /** Пины управления колесами. */
        const uint8_t WHEEL_LEFT_BACKWARD = 2, WHEEL_LEFT_FORWARD = 3; 
        const uint8_t WHEEL_RIGHT_BACKWARD = 4, WHEEL_RIGHT_FORWARD = 5;

        /** Скорость изменения ШИМ сигнала в миллисекундах */
        const uint16_t PWM_CHANGE_RATE = 1000;

        /**
         * Управление движением.
         * 
         * @param distance расстояние до препятствия в сантиметрах.
         */
        void drive(uint16_t distance) 
        {
            /** На данном этапе программы поворот налево и движение назад не используется, но оно будет необходимо в дальнейшем! */

            // const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
            // const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1, MOVE_BACKWARD = 2;

            const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_RIGHT = 2;
            const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1;

            uint8_t speed, speedForTurn;

            speed = valueSpeed(distance);
            speedForTurn = valueForTurn(distance, speed);

                   if (distance < 15) {
                turn(MOVE_IN_PLACE, DIRECTION_RIGHT);
            } else if (distance < 40) {
                turn(MOVE_FORWARD, DIRECTION_RIGHT, speed, speedForTurn);
            } else {
                turn(MOVE_FORWARD, DIRECTION_NO_TURN, speed);
            }
        }

    private:
        /** Переменная используется для плавного разгона/остановки. */
        uint8_t *prevValue = 0;

        /**
         * Скорость движения в зависимости от дистанции до препятствии.
         * 
         * @param distance расстояние до препятствия в сантиметрах
         * @return текущая частота ШИМ сигнала моторов
         */
        uint8_t valueSpeed(uint16_t distance) 
        {
            uint8_t pwm;

                   if (distance < 20) {  
                pwm = 30;
            } else if (distance < 30) {
                pwm = 60;
            } else if (distance < 40) {
                pwm = 125;
            } else if (distance < 50) {
                pwm = 175;
            } else {
                pwm = 200;
            }

            return pwm;
        }

        /**
         * Значение ШИМ сигнала для поворота. В зависимости от расстояния до препятствия увеличивается
         * резкость поворота.
         * 
         * @param distance - расстояние до препятствия
         * @param speed - скорость движения техники
         * @return частота ШИМ сигнала моторов для поворота
         */
        uint8_t valueForTurn(uint16_t distance, uint8_t speed)
        {
            int8_t percentReduction;

            if (distance < 20) {
                percentReduction = 80;
            } else if (distance < 40) {
                percentReduction = 60; // снижение скорости на n%
            } else {
                percentReduction = 50;
            }
            
            return (speed - (speed * abs(percentReduction) * 0.01));
        }

        /**
         * Различные движения машины, путем установки ШИМ сигнала.
         * 
         * @param directionMove направление движения, 0 - вперед, 1 - на месте, 2 - назад
         * @param directionTurn направление поворота, 0 - без поворотов, 1 - влуво, 2 - вправо
         * @param normalSpeed скорость движения
         * @param slowSpeed низкая скорость движения для возможности поворотов
         */
        void turn(uint8_t directionMove, uint8_t directionTurn, uint8_t normalSpeed = 255, uint8_t slowSpeed = 255) 
        {            
            digitalWrite(WHEEL_LEFT_FORWARD, LOW);
            digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
            digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
            digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);

            if (directionMove == 0) { // движение вперед
                switch (directionTurn) {
                    case 0: // не поворачиваем
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, normalSpeed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, normalSpeed);
                        break;
                    case 1: // поворот влево
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, slowSpeed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, normalSpeed);
                        break;
                    case 2: // поворот вправо
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, normalSpeed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, slowSpeed);
                        break;
                }
            } else if (directionMove == 1) { // движение на месте
                switch (directionTurn) {
                    case 0: // стоп
                        analogWriteSmooth(WHEEL_LEFT_BACKWARD, 0);
                        analogWriteSmooth(WHEEL_RIGHT_BACKWARD, 0);
                    case 1: // разворот налево
                        analogWriteSmooth(WHEEL_LEFT_BACKWARD, normalSpeed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, normalSpeed);
                        break;
                    case 2: // разворот направо
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, normalSpeed);
                        analogWriteSmooth(WHEEL_RIGHT_BACKWARD, normalSpeed);
                        break;
                }
            } else if (directionMove == 2) { // движение назад
                // не реализовано
            }
        }

        /** Плавное изменение ШИМ значения. */
        void analogWriteSmooth(uint8_t pin, uint8_t value)
        {
            uint8_t step = PWM_CHANGE_RATE / abs(prevValue[pin] - value);

            while (prevValue[pin] != value) {
                if (prevValue[pin] < value) {
                    prevValue[pin]++;
                } else {
                    prevValue[pin]--;
                }
                analogWrite(pin, prevValue[pin]);
                delay(step);
            }

            analogWrite(pin, value);
        }
};