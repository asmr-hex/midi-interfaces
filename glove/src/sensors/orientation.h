#ifndef ORIENTATION_SENSOR_H_
#define ORIENTATION_SENSOR_H_

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include "sensor.h"


namespace sensor {
  
  class Orientation : public Adafruit_BNO055, public sensor::Sensor {
  public:
    
    Orientation(midi::MidiInterface<HardwareSerial>* midi_interface,
                sensor::MidiDispatcher dispatch=sensor::default_midi_dispatcher,
                sensor::range_t input_range={0, 127},
                sensor::range_t output_range={0, 127},
                bool invert_values=false,
                bool debug=false);
    void read();
    void send();

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };
  
}

#endif
