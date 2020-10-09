#include <Arduino.h>

#include "characteristics.h"

#include "Movement.h"
#include "reflexes/Moving.h"
#include "reflexes/Vision.h"
#include "sensors/Laser.h"
#include "sensors/Ultrasound.h"
#include "Vector.h"

Movement MovementObject;

Moving MovingObject;
Vision VisionObject;

Laser LaserObject;
Ultrasound UltrasoundObject;

Vector VectorObject;

void setup();