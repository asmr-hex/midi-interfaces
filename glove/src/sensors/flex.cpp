#include <Arduino.h>

#include "flex.h"


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

void sensor::Flex::read() {
  this->v = this->transform(analogRead(this->pin));
}

void sensor::Flex::send() {
  // run dispatcher by injecting the midi interface
  this->dispatch(this->midi_interface);
}
