#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>
#include <MIDI.h>
#include "sensors/sensor.h"



class Config {
public:
  Config(bool debug = false) : debug(debug) {}

  bool debug;
};

#endif
