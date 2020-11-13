#include "main.h"

/**
 * Разобраться в классе Movement, лишние кейсы.
 */

  Movement MovementObject;
  Vector VectorObject;
  Moving MovingObject;
  Vision VisionObject;
  Laser LaserObject;

  Ultrasound UltrasoundFrontLeft;
  Ultrasound UltrasoundFrontRight;
  Ultrasound UltrasoundLeft;
  Ultrasound UltrasoundRight;

void setup() {
  TCCR3B = (TCCR3B & 0xe0) | 0x05; // ШИМ двигателя

  pinMode(SPEAKER, OUTPUT);

  MovementObject.init();
  LaserObject.init();
  
  UltrasoundFrontLeft.setPin(ULTRASOUND_FRONT_LEFT);
  UltrasoundFrontRight.setPin(ULTRASOUND_FRONT_RIGHT);
  UltrasoundLeft.setPin(ULTRASOUND_LEFT);
  UltrasoundRight.setPin(ULTRASOUND_RIGHT);

  for (;;) {
    MovingObject.main();
  }
}
