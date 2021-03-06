#pragma once

#include <Arduino.h>

/** Пины лазерных датчиков */
const uint8_t LASER_LEFT = 40;
const uint8_t LASER_RIGHT = 38;

/** Пины ультразвуковых датчиков HC-SR04, где первый элемент trig, второй echo */
const uint8_t ULTRASOUND_FRONT_LEFT[2] = {24, 22};
const uint8_t ULTRASOUND_FRONT_RIGHT[2] = {28, 26}; 
const uint8_t ULTRASOUND_LEFT[2] = {31, 33};
const uint8_t ULTRASOUND_RIGHT[2] = {32, 30};

/** Пины двигателей */
const uint8_t WHEEL_LEFT_BACKWARD = 23;
const uint8_t WHEEL_LEFT_FORWARD = 25;
const uint8_t WHEEL_LEFT_PWM = 2;
const uint8_t WHEEL_RIGHT_BACKWARD = 27;
const uint8_t WHEEL_RIGHT_FORWARD = 29;
const uint8_t WHEEL_RIGHT_PWM = 3;

/** Пьезодинамик */
const uint8_t SPEAKER = 8;