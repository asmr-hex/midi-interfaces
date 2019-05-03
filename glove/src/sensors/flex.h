#ifndef FLEX_SENSOR_H_
#define FLEX_SENSOR_H_

#include <Arduino.h>
#include "config.h"
#include "util.h"


namespace sensor {

  class Flex {
  public:
    
    Flex(sensor::Config config = {});
    void read(uint8_t pin);

    sensor::Config config;
    int v;
    
  private:
    int transform(int value);

    range_t input_range;
    range_t output_range;
  };
  
}

#endif
