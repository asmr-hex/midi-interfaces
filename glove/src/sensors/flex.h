#ifndef FLEX_SENSOR_H_
#define FLEX_SENSOR_H_

#include <Arduino.h>
#include "sensor.h"


namespace sensor {

  class Flex : public sensor::Sensor {
  public:
    Flex(byte pin,
         midi::MidiInterface<HardwareSerial>* midi_interface,
         sensor::MidiDispatcher dispatch=sensor::default_midi_dispatcher,
         sensor::range_t input_range={0, 127},
         sensor::range_t output_range={0, 127},
         bool invert_values=true,
         bool debug=false)
      : pin(pin),
        sensor::Sensor(midi_interface,
                       dispatch,
                       input_range,
                       output_range,
                       invert_values,
                       debug)
    {};
    void read();
    void send();

    byte pin;
    int v=0;
    
  private:
    int transform(int value);

  };
  
}

#endif
