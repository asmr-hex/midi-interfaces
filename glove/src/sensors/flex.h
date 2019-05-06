#ifndef FLEX_SENSOR_H_
#define FLEX_SENSOR_H_

#include <Arduino.h>
#include "sensor.h"


namespace sensor {

  class Flex : public sensor::Sensor {
  public:
    enum dispatcher_t {Debug, Weirdo};

    Flex(byte pin,
         midi::MidiInterface<HardwareSerial>* midi_interface,
         dispatcher_t dispatcher_type=Flex::Debug,
         sensor::range_t input_range={0, 127},
         sensor::range_t output_range={0, 127},
         bool invert_values=true,
         bool debug=false)
      : pin(pin),
        sensor::Sensor(midi_interface,
                       input_range,
                       output_range,
                       invert_values,
                       debug)
    {
      dispatchers[Flex::Debug] = &Flex::debug_dispatcher;
      dispatchers[Flex::Weirdo] = &Flex::weird_dispatcher;
      
      dispatcher = dispatchers[dispatcher_type];
    };
    void setDispatcher(int type);
    void read();
    void send();

    // enum _DispatcherTypes {Serial, Weirdo};
    // static _DispatcherTypes DispatcherTypes;

    typedef void (Flex::*Dispatcher)();
    Dispatcher dispatchers[2];
    Dispatcher dispatcher;
    
    byte pin;
    int v=0;
    
  private:
    int transform(int value);

    /* dispatchers */
    void debug_dispatcher();
    void weird_dispatcher();

  };
  
}

#endif
