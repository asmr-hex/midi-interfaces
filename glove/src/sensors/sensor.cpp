#include <Arduino.h>
#include <MIDI.h>

#include "sensor.h"


bool sensor::Sensor::debounce(int current_value) {
  // compute new running average
  running_average[1] = (running_average[1] + current_value) / 2;

  if ( abs(running_average[1] - running_average[0]) > debounce_threshold) {
    running_average[0] = running_average[1];
    
    return false;
  }

  return true;
}
