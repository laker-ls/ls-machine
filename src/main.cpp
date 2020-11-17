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

uint8_t currentSpeed = 0;
uint8_t needSpeed = 0;

void setup() {
  MoveAutomatismObject.init();

  LaserSenseLeft.init(LASER_LEFT);
  LaserSenseRight.init(LASER_RIGHT);
  
  setPinUltrasoundSenses();
  settingTimers();

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
  Timer1 Timer1Object; 
  Timer1Object.setInterval(8); // для плавного изменения шим моторов

  Timer3 Timer3Object; 
  Timer3Object.setDividerRegister(1024); // для безшумной частоты шим на двигатели
}
