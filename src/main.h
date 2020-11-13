#include <Arduino.h>

#include "characteristics.h"

#include "logics/Movement.h"
#include "Vector.h"
#include "reflexes/Moving.h"
#include "reflexes/Vision.h"
#include "sensors/Laser.h"
#include "sensors/Ultrasound.h"

extern Movement MovementObject;
extern Vector VectorObject;
extern Moving MovingObject;
extern Vision VisionObject;
extern Laser LaserObject;
extern Ultrasound UltrasoundFrontLeft;
extern Ultrasound UltrasoundFrontRight;
extern Ultrasound UltrasoundLeft;
extern Ultrasound UltrasoundRight;

void setup();

void marsh();