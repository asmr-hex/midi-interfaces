#include "flex.h"
#include "config.h"
#include <Arduino.h>


sensor::Flex::Flex(sensor::Config config)
  : input_range({0, 100}),
    output_range({0,100}),
    config(config)
{}

int sensor::Flex::transform(int value) {
  // bound the value
  value = constrain(value, this->input_range.min, this->input_range.max);

  if ( this->config.invert_values ) {
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

void sensor::Flex::read(uint8_t pin) {
  int raw_value = analogRead(pin);
  
  this->v = analogRead(A0);
}
