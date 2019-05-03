#include "glove.h"
#include "sensors/flex.h"
#include "sensors/orientation.h"


Glove::Glove() {
  // initialize finger flex sensors
  size_t n = sizeof(fingers)/sizeof(fingers[0]);
  for (byte i = 0; i < n; i++) {
    fingers[i] = new sensor::Flex();
  }

  // initialize orientation sensor
  orientation = new sensor::Orientation();

  Midi((HardwareSerial&)Serial)
}

