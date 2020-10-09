#include <Arduino.h>

#include "characteristics.h"

#include "Movement.h"
#include "Vector.h"
#include "reflexes/Moving.h"
#include "reflexes/Vision.h"
#include "sensors/Laser.h"
#include "sensors/Ultrasound.h"

Movement MovementObject;
Vector VectorObject;

Moving MovingObject;
Vision VisionObject;

Laser LaserObject;
Ultrasound UltrasoundObject;

void setup();