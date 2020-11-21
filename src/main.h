#include <Arduino.h>

#include "physicalParameters/bodyParameters.h"
#include "physicalParameters/pinsParameters.h"

#include "brains/automatisms/MoveAutomatism.h"
#include "brains/logics/Move/MoveLogic.h"
#include "brains/automatisms/VisionAutomatism.h"
#include "brains/senseOrgans/vision/LaserSense.h"
#include "brains/senseOrgans/vision/UltrasoundSense.h"
#include "brains/automatisms/SpeakerAutomatism.h"

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
extern SpeakerAutomatism SpeakerAutomatismObject;

void setup();
void setPinUltrasoundSenses();
void settingTimers();
