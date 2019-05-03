#ifndef GLOVE_H_
#define GLOVE_H_

#include <MIDI.h>
#include <Arduino.h>
#include "sensors/flex.h"
#include "sensors/orientation.h"


enum finger { thumb, index, middle, ring, pinkey };

class Glove {
public:
  Glove();

private:
  midi::MidiInterface<HardwareSerial> Midi;
  sensor::Flex *fingers[5];
  sensor::Orientation *orientation;
};

#endif
