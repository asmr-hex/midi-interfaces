#ifndef SENSOR_BASE_H_
#define SENSOR_BASE_H_

#include <Arduino.h>
#include <MIDI.h>


namespace sensor {

  // midi dispatcher function type
  typedef void (*MidiDispatcher)(midi::MidiInterface<HardwareSerial>*);

  // default midi dispatcher
  void default_midi_dispatcher(midi::MidiInterface<HardwareSerial>* m) {}

  // range_t defines a one-dimensional value range.
  struct range_t {
    double max;
    double min;
  };

  class Sensor {
  public:
    Sensor(midi::MidiInterface<HardwareSerial>* midi_interface,
           MidiDispatcher dispatch,
           range_t input_range,
           range_t output_range,
           bool invert_values,
           bool debug)
      : input_range(input_range),
        output_range(output_range),
        invert_values(invert_values),
        midi_interface(midi_interface),
        dispatch(dispatch),
        debug(debug)
    {}

    range_t input_range;
    range_t output_range;
    bool invert_values;
    midi::MidiInterface<HardwareSerial>* midi_interface;
    MidiDispatcher dispatch;
    bool debug;
  };

}

#endif
