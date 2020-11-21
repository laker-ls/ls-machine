#include <Arduino.h>
#include "brains/logics/Move/MoveLogic.h"
#include "brains/automatisms/SpeakerAutomatism.h"

void setup() {
  MoveLogic MoveLogicObject;
  SpeakerAutomatism SpeakerAutomatismObject;

  MoveLogicObject.init();
  SpeakerAutomatismObject.init();
  SpeakerAutomatismObject.wokeUp();

  for (;;) {
    MoveLogicObject.main();
  }
}
