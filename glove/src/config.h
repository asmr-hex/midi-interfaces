#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>
#include <MIDI.h>
#include "sensors/sensor.h"


enum dispatch_funcs { SerialPrint };

// void serial_print_dispatcher(midi::MidiInterface<HardwareSerial>* midi_interface) {
  
// }

class Config {
public:
  Config(bool debug = false) : debug(debug) {
    // this->dispatchers[SerialPrint] = serial_print_dispatcher;
  };

  //sensor::MidiDispatcher dispatchers[1];
  bool debug = false;
  
};

#endif
