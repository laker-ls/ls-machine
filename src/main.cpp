#include "main.h"

void setup() {
  MoveLogicObject.init();
  SpeakerAutomatismObject.init();
  SpeakerAutomatismObject.wokeUp();

  for (;;) {
    MoveLogicObject.main();
  }
}
