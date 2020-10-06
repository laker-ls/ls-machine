/**
 * Файл Characteristics является набором констант, в которых определены различные физические характеристики робота.
 */
#pragma once
#include <Arduino.h>

const float BODY_WIDTH = 180;
const float BODY_LENGTH = 220;
const uint8_t DISTANCE_BETWEEN_LASER = 145; // расстояние между двумя фронтальными лазерами
const uint16_t LASER_DISTANCE_LIMIT = 1200;

const float WHEEL_DIAMETER = 65;
const float MOTOR_VOLTAGE = 7.6;

/** Пины лазерных датчиков */
const uint8_t LASER_LEFT = 40;
const uint8_t LASER_RIGHT = 38;

/** Пины ультразвуковых датчиков */
const uint8_t ULTRASOUND_FRONT[2] = {51, 50}; // HC-SR04, где первый элемент trig, второй echo

/** Пины двигателей */
const uint8_t WHEEL_LEFT_BACKWARD = 23;
const uint8_t WHEEL_LEFT_FORWARD = 25;
const uint8_t WHEEL_LEFT_PWM = 2;
const uint8_t WHEEL_RIGHT_BACKWARD = 27;
const uint8_t WHEEL_RIGHT_FORWARD = 29;
const uint8_t WHEEL_RIGHT_PWM = 3;