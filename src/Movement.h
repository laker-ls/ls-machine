#pragma once
#include <Arduino.h>

/**
 * Всё связанное с работой двигателей.
 */
class Movement 
{
    public:
        /**
         * Управление движением.
         * 
         * @param distanceFront расстояние спереди до препятствия в сантиметрах.
         * @param distanceLeft расстояние слева до препятствия в сантиметрах
         * @param distanceRight расстояние справа до препятствия в сантиметрах
         */
        void drive(uint16_t distanceFront) 
        {
            /** На данном этапе программы поворот налево и движение назад не используется, но оно будет необходимо в дальнейшем! */

            const uint8_t DIRECTION_NO_TURN = 0, DIRECTION_LEFT = 1, DIRECTION_RIGHT = 2;
            const uint8_t MOVE_FORWARD = 0, MOVE_IN_PLACE = 1, MOVE_BACKWARD = 2;
            const uint16_t DISTANCE_CRITICAL = 30, DISTANCE_SMALL = 60, DISTANCE_NORMAL = 150, DISTANCE_LARGE = 300;
            const uint8_t SPEED_SMALL = 30, SPEED_NORMAL = 80, SPEED_LARGE = 100, SPEED_MAXIMUM = 120; // напряжение 12В, не использовать максимальный ШИМ

            if (distanceFront < DISTANCE_CRITICAL) {
                turn(MOVE_BACKWARD, DIRECTION_NO_TURN, SPEED_NORMAL);
            } else if (distanceFront < DISTANCE_SMALL) {
                turn(MOVE_IN_PLACE, DIRECTION_RIGHT, SPEED_NORMAL);
            } else if (distanceFront < DISTANCE_NORMAL) {
                turn(MOVE_FORWARD, DIRECTION_NO_TURN, SPEED_NORMAL);
            } else {
                turn(MOVE_FORWARD, DIRECTION_NO_TURN, SPEED_LARGE);
            }
        }

        /** Настройка пинов */
        void pinModeSet() {
            pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);
            pinMode(WHEEL_LEFT_FORWARD, OUTPUT);
            pinMode(WHEEL_RIGHT_BACKWARD, OUTPUT);
            pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);
        }

    private:
        /** Пины управления колесами. */
        const uint8_t WHEEL_LEFT_BACKWARD = 2, WHEEL_LEFT_FORWARD = 3; 
        const uint8_t WHEEL_RIGHT_BACKWARD = 4, WHEEL_RIGHT_FORWARD = 5;

        /** Скорость изменения ШИМ сигнала в миллисекундах */
        const uint16_t PWM_CHANGE_RATE = 1;

        /** Переменная используется для плавного разгона/остановки. */
        uint8_t *prevValue = 0;
        

        /**
         * Различные движения машины, путем установки ШИМ сигнала.
         * 
         * @param directionMove направление движения, 0 - вперед, 1 - на месте, 2 - назад
         * @param directionTurn направление поворота, 0 - без поворотов, 1 - влево, 2 - вправо
         * @param speed скорость движения
         * @param angleRotation угол на который необходимо повернуть
         */
        void turn(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint16_t angleRotation) 
        {            
            digitalWrite(WHEEL_LEFT_FORWARD, LOW);
            digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
            digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
            digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);

            if (directionMove == 0) { // движение вперед
                switch (directionTurn) {
                    case 0: // не поворачиваем
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, speed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, speed);
                        break;
                    case 1: // поворот влево
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, speed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, speed);
                        break;
                    case 2: // поворот вправо
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, speed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, speed);
                        break;
                }
            } else if (directionMove == 1) { // движение на месте
                switch (directionTurn) {
                    case 0: // стоп
                        analogWriteSmooth(WHEEL_LEFT_BACKWARD, 0);
                        analogWriteSmooth(WHEEL_RIGHT_BACKWARD, 0);
                    case 1: // разворот налево
                        analogWriteSmooth(WHEEL_LEFT_BACKWARD, speed);
                        analogWriteSmooth(WHEEL_RIGHT_FORWARD, speed);
                        break;
                    case 2: // разворот направо
                        analogWriteSmooth(WHEEL_LEFT_FORWARD, speed);
                        analogWriteSmooth(WHEEL_RIGHT_BACKWARD, speed);
                        break;
                }
            } else if (directionMove == 2) { // движение назад
                analogWriteSmooth(WHEEL_LEFT_BACKWARD, speed);
                analogWriteSmooth(WHEEL_RIGHT_BACKWARD, speed);

                delay(1000);
            }
        }

        /** Плавное изменение ШИМ значения. */
        void analogWriteSmooth(uint8_t pin, uint8_t value)
        {
            uint8_t step = PWM_CHANGE_RATE / abs(prevValue[pin] - value);

            // while (prevValue[pin] != value) {
            //     if (prevValue[pin] < value) {
            //         prevValue[pin]++;
            //     } else {
            //         prevValue[pin]--;
            //     }
            //     analogWrite(pin, prevValue[pin]);
            //     delay(step);
            // }

            analogWrite(pin, value);
        }
};