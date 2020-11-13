#include "main.h"

void Movement::init()
{
    pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);
    pinMode(WHEEL_LEFT_FORWARD, OUTPUT);
    pinMode(WHEEL_RIGHT_BACKWARD, OUTPUT);
    pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);
}

void Movement::turn(uint8_t directionMove, uint8_t directionTurn, uint8_t speed, uint16_t angleRotation) 
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
                analogWrite(WHEEL_LEFT_PWM, 50);

                digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                analogWrite(WHEEL_RIGHT_PWM, speed);
                break;
            case 2: // поворот вправо
                digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
                analogWrite(WHEEL_LEFT_PWM, speed);

                digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
                analogWrite(WHEEL_RIGHT_PWM, 50);
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

void Movement::delayTurn(uint16_t degree, uint8_t sideFaster, uint8_t sideSlow)
{
    float sideFasterInMm = VectorObject.millimetersPerSecond(sideFaster);
    float sideSlowInMm = VectorObject.millimetersPerSecond(sideSlow);
    
    uint16_t time = VectorObject.timeForTurn(degree, sideFasterInMm, sideSlowInMm);

    delay(time); // 1700 = 360
}
