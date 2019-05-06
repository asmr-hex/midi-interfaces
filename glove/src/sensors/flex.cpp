#include <Arduino.h>

#include "flex.h"


bool sensor::Flex::value_changed() {
  if ( v >= delta_threshold + previous_v || v <= delta_threshold - previous_v ) {
    return true;
  }

  return false;
}

int sensor::Flex::transform(int value) {

  return value;
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
  if (this->value_changed()) {
    // run dispatcher by injecting the midi interface
    (*this.*dispatcher)();
    previous_v = v;
  }
}

void sensor::Flex::debug_dispatcher() {
  Serial.print(this->pin - 54);
  Serial.print(": ");
  Serial.println(this->v);
}

void sensor::Flex::weird_dispatcher() {
  Serial.println("WEIRDOOOOO");
}
