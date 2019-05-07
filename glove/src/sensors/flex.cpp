#include <Arduino.h>

#include "flex.h"


void sensor::Flex::calibrate(sensor::calibration_t calibration_bound) {
  // read value
  this->read(false);
  int new_value = this->v;

  switch (calibration_bound) {
  case sensor::CalibrateUpperBound:
    this->input_range.max = (this->input_range.max + new_value) / 2;
    break;
  case sensor::CalibrateLowerBound:
    this->input_range.min = (this->input_range.min + new_value) / 2;
    break;
  }
}

int sensor::Flex::transform(int value) {

  // bound the value
  value = constrain(value, this->input_range.min, this->input_range.max);

  if ( this->invert_values ) {
    // the input values should be inverted
    value = (this->input_range.max - value) + this->input_range.min;
  }
  
  // re-map the constrained value to a new range
  value = map(value,
              this->input_range.min,
              this->input_range.max,
              this->output_range.min,
              this->output_range.max);

  return value;
}

void sensor::Flex::read(bool do_transform) {
  int new_value = analogRead(this->pin);

  if (do_transform) {
    new_value = transform(new_value);
  }
  
  this->v = new_value;
}

void sensor::Flex::send() {
  // run dispatcher by injecting the midi interface
  (*this.*dispatcher)();
}

void sensor::Flex::debug_dispatcher() {
  Serial.print(this->pin - 54);
  Serial.print(": ");
  Serial.print(this->v);
  Serial.print("   ");
}

void sensor::Flex::weird_dispatcher() {
  Serial.println("WEIRDOOOOO");
}

void sensor::Flex::midi_cc_dispatcher() {
  this->midi_interface->sendControlChange(this->midi_cc_number, this->v, this->midi_channel);
}
