#include <Arduino.h>
#include <MIDI.h>
#include "glove.h"
#include "config.h"
#include "sensors/flex.h"
#include "sensors/orientation.h"
#include "sensors/sensor.h"


Glove::Glove(Config config)
  : config(config)
{
  // instantiate a new midi interface
  midi_interface = new midi::MidiInterface<HardwareSerial>((HardwareSerial&)Serial);

  // TODO (coco|5.4.2019) incorporate this into config
  byte pins[] = {A0, A1, A2, A3, A4};
  
  // initialize finger flex sensors
  size_t n = sizeof(fingers)/sizeof(fingers[0]);
  for (byte i = 0; i < n; i++) {
    fingers[i] = new sensor::Flex(pins[i],
                                  midi_interface,
                                  sensor::default_midi_dispatcher,// this->config.dispatchers[dispatch_funcs::SerialPrint],
                                  {400, 800},
                                  {400, 800},
                                  false,
                                  true);
  }

  // initialize orientation sensor
  // orientation = new sensor::Orientation();
}

void Glove::setup() {
  if ( this->config.debug ) {
    // start midi interface
    this->midi_interface->begin();
  } else {
    // start serial communication
    Serial.begin(9600);
  }
}

// read all the connected sensors
void Glove::read_and_dispatch() {
  // read from finger sensors and send messages
  for (sensor::Flex *finger : this->fingers) {
    finger->read();
    finger->send();
  }

  // read orientation sensor and send messages
  // this->orientation.read();
  // this->orientation.send();
}
