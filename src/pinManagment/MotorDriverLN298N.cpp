#include "pinManagment/MotorDriverLN298N.h"

void MotorDriverLN298N::setPins()
{
    pinMode(WHEEL_LEFT_BACKWARD, OUTPUT);
    pinMode(WHEEL_LEFT_FORWARD, OUTPUT);
    pinMode(WHEEL_RIGHT_BACKWARD, OUTPUT);
    pinMode(WHEEL_RIGHT_FORWARD, OUTPUT);
}

void MotorDriverLN298N::moveForward(uint8_t speed)
{
    digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
    analogWrite(WHEEL_LEFT_PWM, speed);

    digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
    analogWrite(WHEEL_RIGHT_PWM, speed);
}

void MotorDriverLN298N::moveLeft(uint8_t speed, uint8_t speedLower)
{
    digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
    analogWrite(WHEEL_LEFT_PWM, speedLower);

    digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
    analogWrite(WHEEL_RIGHT_PWM, speed);

}

void MotorDriverLN298N::moveRight(uint8_t speed, uint8_t speedLower)
{
    digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
    analogWrite(WHEEL_LEFT_PWM, speed);

    digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
    analogWrite(WHEEL_RIGHT_PWM, speedLower);
}

void MotorDriverLN298N::moveInPlaceStop()
{
    digitalWrite(WHEEL_LEFT_FORWARD, LOW);
    digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
    analogWrite(WHEEL_LEFT_PWM, 0);

    digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
    digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
    analogWrite(WHEEL_RIGHT_PWM, 0);
}

void MotorDriverLN298N::moveInPlaceLeft(uint8_t speed)
{
    digitalWrite(WHEEL_LEFT_FORWARD, LOW);
    digitalWrite(WHEEL_LEFT_BACKWARD, HIGH);
    analogWrite(WHEEL_LEFT_PWM, speed);

    digitalWrite(WHEEL_RIGHT_FORWARD, HIGH);
    digitalWrite(WHEEL_RIGHT_BACKWARD, LOW);
    analogWrite(WHEEL_RIGHT_PWM, speed);
}

void MotorDriverLN298N::moveInPlaceRight(uint8_t speed)
{
    digitalWrite(WHEEL_LEFT_FORWARD, HIGH);
    digitalWrite(WHEEL_LEFT_BACKWARD, LOW);
    analogWrite(WHEEL_LEFT_PWM, speed);

    digitalWrite(WHEEL_RIGHT_FORWARD, LOW);
    digitalWrite(WHEEL_RIGHT_BACKWARD, HIGH);
    analogWrite(WHEEL_RIGHT_PWM, speed);
}