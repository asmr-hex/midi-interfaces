#ifndef GLOVE_H_
#define GLOVE_H_

#include <MIDI.h>
#include <Arduino.h>
#include "sensors/flex.h"
#include "sensors/orientation.h"
#include "config.h"


enum finger { thumb, index, middle, ring, pinkey };

class Glove {
public:
  Glove(Config config = {});
  void setup();
  void calibrate(int seconds);
  void read_and_dispatch();

  Config config;

private:
  midi::MidiInterface<HardwareSerial> *midi_interface;
  sensor::Flex *fingers[5];
  sensor::Orientation *orientation;

  int dt = 500; // ms
};

#endif
