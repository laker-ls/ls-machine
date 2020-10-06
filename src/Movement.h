#pragma once
#include <Arduino.h>
#include "Characteristics.h"
#include "Vector.h"

/**
 * Всё связанное с работой двигателей.
 */
class Movement
{
    public:
        Vector VectorObject;

        Movement()
        {
            pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);
            pinMode(WHEEL_LEFT_FORWARD, OUTPUT);
            pinMode(WHEEL_RIGHT_BACKWARD, OUTPUT);
            pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);
        }

        /**
         * Различные движения машины, путем установки ШИМ сигнала.
         * 
         * @param directionMove направление движения, 0 - вперед, 1 - на месте
         * @param directionTurn направление поворота, 0 - без поворотов, 1 - влево, 2 - вправо
         * @param speed скорость движения
         * @param angleRotation угол на который необходимо повернуть
         */
        void turn(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint16_t angleRotation) 
        {            
            if (directionMove == 0) { // движение вперед
                digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
                digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
                switch (directionTurn) {
                    case 0: // не поворачиваем
                        digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
                        analogWrite(WHEEL_LEFT_PWM, speed);

                        digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                        analogWrite(WHEEL_RIGHT_PWM, speed);
                        break;
                    case 1: // поворот влево
                        digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
                        analogWrite(WHEEL_LEFT_PWM, speed);

                        digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                        analogWrite(WHEEL_RIGHT_PWM, speed);
                        break;
                    case 2: // поворот вправо
                        digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
                        analogWrite(WHEEL_LEFT_PWM, speed);

                        digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                        analogWrite(WHEEL_RIGHT_PWM, speed);
                        break;
                }
            } else if (directionMove == 1) { // движение на месте
                switch (directionTurn) {
                    case 0: // стоп
                        digitalWrite(WHEEL_LEFT_FORWARD, LOW);
                        digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
                        analogWrite(WHEEL_LEFT_PWM, 0);

                        digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
                        digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
                        analogWrite(WHEEL_RIGHT_PWM, 0);
                        break;
                    case 1: // разворот налево
                        digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
                        digitalWrite(WHEEL_LEFT_FORWARD, LOW);
                        analogWrite(WHEEL_LEFT_PWM, speed);

                        digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                        digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
                        analogWrite(WHEEL_RIGHT_PWM, speed);
                        break;
                    case 2: // разворот направо
                        digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
                        digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
                        analogWrite(WHEEL_LEFT_PWM, speed);

                        digitalWrite(WHEEL_RIGHT_BACKWARD, HIGH);
                        digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
                        analogWrite(WHEEL_RIGHT_PWM, speed);
                        break;
                }
                
                delayTurn(angleRotation, speed, 0);
            }
        }

        /**
         * Поворот на указанное количество градусов.
         * 
         * @param degree градусы, на которые необходимо развернуть транспорт
         * @param sideFaster скорость в PWM борта имеющего большую скорость движения
         * @param sideSlow скорость в PWM борта имеющего меньшую скорость движения
         */
        void delayTurn(uint16_t degree, uint8_t sideFaster, uint8_t sideSlow)
        {
            float sideFasterInMm = VectorObject.millimetersPerSecond(sideFaster);
            float sideSlowInMm = VectorObject.millimetersPerSecond(sideSlow);
            
            uint16_t time = VectorObject.timeForTurn(degree, sideFasterInMm, sideSlowInMm);

            delay(time); // 1700 = 360
        }
    
    private:
        /** Переменная используется для плавного разгона/остановки. */
        uint8_t prevValue[256];
        /** Плавное изменение ШИМ значения. */
        void analogWriteSmooth(uint8_t pin, uint8_t value)
        {
            // const uint16_t PWM_CHANGE_RATE = 3000; // Скорость изменения ШИМ сигнала в миллисекундах
            // uint8_t step = PWM_CHANGE_RATE / abs(prevValue[pin] - value);

            // while (prevValue[pin] < value) {
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