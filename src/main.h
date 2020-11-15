#include <Arduino.h>

#include "physicalParameters/bodyParameters.h"
#include "physicalParameters/pinsParameters.h"

#include "brains/automatisms/MoveAutomatism.h"
#include "brains/logics/MoveLogic.h"
#include "brains/automatisms/VisionAutomatism.h"
#include "brains/senseOrgans/vision/LaserSense.h"
#include "brains/senseOrgans/vision/UltrasoundSense.h"

#include "registers/Timer1.h"
#include "registers/Timer3.h"

extern MoveAutomatism MoveAutomatismObject;
extern MoveLogic MoveLogicObject;
extern VisionAutomatism VisionAutomatismObject;
extern LaserSense LaserSenseLeft;
extern LaserSense LaserSenseRight;
extern UltrasoundSense UltrasoundSenseFrontLeft;
extern UltrasoundSense UltrasoundSenseFrontRight;
extern UltrasoundSense UltrasoundSenseLeft;
extern UltrasoundSense UltrasoundSenseRight;

void setup();
void setPinUltrasoundSenses();
void settingTimers();
