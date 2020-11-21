#include "main.h"

MoveAutomatism MoveAutomatismObject;
MoveLogic MoveLogicObject;
VisionAutomatism VisionAutomatismObject;

LaserSense LaserSenseLeft;
LaserSense LaserSenseRight;

UltrasoundSense UltrasoundSenseFrontLeft;
UltrasoundSense UltrasoundSenseFrontRight;
UltrasoundSense UltrasoundSenseLeft;
UltrasoundSense UltrasoundSenseRight;

SpeakerAutomatism SpeakerAutomatismObject;

uint8_t currentSpeed = 0;
uint8_t needSpeed = 0;

void setup() {
  MoveLogicObject.init();
  MoveAutomatismObject.init();

  LaserSenseLeft.init(LASER_LEFT);
  LaserSenseRight.init(LASER_RIGHT);
  
  setPinUltrasoundSenses();
  settingTimers();

  SpeakerAutomatismObject.init();
  SpeakerAutomatismObject.wokeUp();

  Serial.begin(9600);

  for (;;) {
    MoveLogicObject.main();
  }
}

void setPinUltrasoundSenses()
{
  UltrasoundSenseFrontLeft.setPins(ULTRASOUND_FRONT_LEFT);
  UltrasoundSenseFrontRight.setPins(ULTRASOUND_FRONT_RIGHT);
  UltrasoundSenseLeft.setPins(ULTRASOUND_LEFT);
  UltrasoundSenseRight.setPins(ULTRASOUND_RIGHT);
}

void settingTimers()
{
  Timer3 Timer3Object; 
  Timer3Object.setDividerRegister(1024); // для безшумной частоты шим на двигатели
}
