#pragma once

#include <Wire.h>
#include <VL53L0X.h>

/**
 * Работа с лазерным датчиком расстояния VL53L0X. 
 */
class Laser
{
    public:
        void init();

        /**
         * @return Расстояние левого лазерного датчика до препятствия в сантиметрах. При отсутствии препятствия возвращается 999.
         */
        uint16_t distanceLeftInCm();

        /**
         * @return Расстояние правого лазерного датчика до препятствия в сантиметрах. При отсутствии препятствия возвращается 999.
         */
        uint16_t distanceRightInCm();

        /**
         * Определение угла препятствия.
         * @param laserLeft расстояние на левом датчике.
         * @param laserRight расстояние на правом датчике.
         * @return угол, под которым находится препятствие.
         */
        int16_t angleOfObject(uint16_t laserLeft, uint16_t laserRight);

    private:
        VL53L0X sensorLeft;
        VL53L0X sensorRight;

        /**
         * @param sensor объект датчика VL53L0X.
         * @return Расстояние до препятствия в миллиметрах.
         */
        uint16_t distanceRaw(VL53L0X sensor);

        /**
         * @param distanceRaw расстояние в миллиметрах.
         * @return Расстояние в сантиметрах, если превышен лимит расстояния (смотрите в файле основных характеристик) возвращается 999.
         */
        uint16_t distanceInCmWithLimit(uint16_t distanceRaw);

        /**
         * Преобразование расстояния из миллиметров в сантиметры. Так же при отстутствия препятствий возвращается 999.
         * @param distance расстояние в миллиметрах.
         * @return расстояние в сантиметрах.
         */
        uint16_t convertInCmWithMaxRange(uint16_t distance);

        /**
         * Обрезка показаний датчика, при значении превышающем максимальное расстояние возвращает 9999.
         * @param distance расстояние в миллиметрах
         * @return расстояние в диапазоне дозволенного, значения превышающие максимальное расстояние возвращаются в виде 9999.
         */
        uint16_t limitDistance(uint16_t distance);
};
