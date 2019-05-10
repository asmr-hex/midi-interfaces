#ifndef ORIENTATION_SENSOR_H_
#define ORIENTATION_SENSOR_H_

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include "sensor.h"


namespace sensor {

  // Interface for the BNO055 orientation sensor. Contains a nested class, Dimension,
  // which inherits from Sensor. An Orientation object will contain three Dimension
  // members representing the xyz sphere.
  class Orientation : public Adafruit_BNO055 {
  public:

    // Interface for a single dimension of the BNO055 orientation sensor.
    class Dimension : public sensor::Sensor {
    public:
      
      enum class DispatcherType {Debug, MidiControlChange};

      Dimension(midi::MidiInterface<HardwareSerial>* midi_interface,
                DispatcherType dispatcher_type=DispatcherType::Debug,
                sensor::range_t input_range={0, 127},
                sensor::range_t output_range={0, 127},
                bool invert_values=false,
                bool apply_transform=true,
                bool debug=false);
      void set_midi_cc_number(byte cc_number) { midi_cc_number = cc_number; }
      void set_dispatcher(DispatcherType type) { dispatcher = dispatchers[static_cast<int>(type)]; }
      int transform(int value);
      void send();

      int v = 0;

      typedef void (Dimension::*Dispatcher)();
      Dispatcher dispatchers[2];
      Dispatcher dispatcher;
      
    private:
      /* dispatchers */
      void debug_dispatcher();
      void midi_cc_dispatcher();

      byte midi_channel = 1;
      byte midi_cc_number = 1;
      bool apply_transform;
    };
    
    Orientation(Dimension *x, Dimension *y, Dimension *z, bool debug=false);

    void read();
    void send();

    Dimension *x;
    Dimension *y;
    Dimension *z;

  private:
    
    bool debug;
  };
  
}

#endif
