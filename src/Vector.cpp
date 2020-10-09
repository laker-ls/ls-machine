#include "main.h"

float Vector::rpm(uint8_t pwm)
{
    const float VOLT_IN_ONE_PWM = (MOTOR_VOLTAGE / 255);
    const float rpmInOneVolt = 47.5;
    float volt = pwm * VOLT_IN_ONE_PWM;
    
    return volt * rpmInOneVolt;
}

float Vector::millimetersPerSecond(uint8_t pwm)
{
    return rpm(pwm) / 60 * circumference(WHEEL_DIAMETER);
}

float Vector::radiusTurnSlowSide(float sideFaster, float sideSlow)
{
    return sideSlow / (sideFaster - sideSlow) * BODY_WIDTH;
}

float Vector::radiusTurnFasterSide(float sideFaster, float sideSlow)
{
    return sideFaster / (sideFaster - sideSlow) * BODY_WIDTH;
}

float Vector::radiusTurnCenter(float sideFaster, float sideSlow)
{
    return (sideFaster + sideSlow) / (sideFaster - sideSlow) * (BODY_WIDTH / 2);
}

float Vector::cornerSpeed(float sideFaster, float sideSlow)
{
    return (sideFaster + sideSlow) / 2;
}

float Vector::circumference(float radius)
{
    return radius * 3.14;
}

float Vector::distanceInDegrees(float circumference, uint16_t degree)
{
    return circumference / 360 * degree;
}

float Vector::timeForTurn(uint16_t degree, float sideFaster, float sideSlow)
{
    // degree 90
    // sidefaster - 523mm
    float angleSpeed = cornerSpeed(sideFaster, sideSlow); // 261mm
    float radiusOfTurn = radiusTurnCenter(sideFaster, sideSlow); // 90mm
    float currentCircumference = circumference(radiusOfTurn); // 282mm
    float currentDistanceInDegrees = distanceInDegrees(currentCircumference, degree); // 204mm
    // return 778

    return currentDistanceInDegrees / angleSpeed * 1000;
}
