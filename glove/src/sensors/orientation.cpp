#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include "orientation.h"
#include "sensor.h"


// Constructs an orientation sensor.
sensor::Orientation::Orientation(sensor::Orientation::Dimension *x,
                                 sensor::Orientation::Dimension *y,
                                 sensor::Orientation::Dimension *z,
                                 bool debug)
  : Adafruit_BNO055(55), x(x), y(y), z(z), debug(debug)
{
  // in order to proceed, we must wait until the orientation sensor has been detected.
  if ( !this->begin() && this->debug ) {
    Serial.print("Yikes! BNO055 sensor was not detected...check your wiring or I2C ADDR!");
    while(1);
  }

  // great, it should have connected at this point

  delay(1000);

  // set the sensor to use an external clock (Arduino clock)
  this->setExtCrystalUse(true);

  if (this->debug) {
    // if we are debugging, always set the dispatchers to debug-mode automatically
    this->x->set_dispatcher(Dimension::DispatcherType::Debug);
    this->y->set_dispatcher(Dimension::DispatcherType::Debug);
    this->z->set_dispatcher(Dimension::DispatcherType::Debug);
  }
} // end Orientation constructor

// read gets the current values of the x, y, z orientation and
// populates the x, y, z values of this object.
void sensor::Orientation::read() {
  sensors_event_t event;
  this->getEvent(&event);

  // transform and assign readings to xyz sensors
  this->x->v = this->x->transform(event.orientation.x);
  this->y->v = this->y->transform(event.orientation.y);
  this->z->v = this->z->transform(event.orientation.z);
}

// dispatch all current sensor readings.
void sensor::Orientation::send() {
  this->x->send();
  this->y->send();
  this->z->send();
}


/* Orientation::Dimension methods */


// Constructs an orientation dimension.
sensor::Orientation::Dimension::Dimension(midi::MidiInterface<HardwareSerial>* midi_interface,
                                          DispatcherType dispatcher_type,
                                          sensor::discontinuous_range_t discont_input_range,
                                          sensor::discontinuous_range_t discont_output_range,
                                          bool invert_values,
                                          bool apply_transform,
                                          bool debug)
  : apply_transform(apply_transform),
    discont_input_range(discont_input_range),
    discont_output_range(discont_output_range),
    sensor::Sensor(midi_interface,
                   sensor::range_t{},
                   sensor::range_t{},
                   invert_values,
                   debug)
{
  // create dispatchers
  dispatchers[static_cast<int>(DispatcherType::Debug)] = &Dimension::debug_dispatcher;
  dispatchers[static_cast<int>(DispatcherType::MidiControlChange)] = &Dimension::midi_cc_dispatcher;
  
  // dispatcher = dispatchers[static_cast<int>(dispatcher_type)];
  this->set_dispatcher(dispatcher_type);
} // end Orientation::Dimension constructor

// Perform transformation of raw input readings.
int sensor::Orientation::Dimension::transform(int value) {
  if (!this->apply_transform) {
    // do nothing if we don't want to apply the transform
    return value;
  }

  // since the orientation dimension measurements span a discontinuous boundary
  // we must map over a discontinuous range
  if (value >= discont_input_range.lower.min && value <= discont_input_range.lower.max) {
    value = map(value,
                this->discont_input_range.lower.min,
                this->discont_input_range.lower.max,
                this->discont_output_range.lower.min,
                this->discont_output_range.lower.max);
  } else if (value >= discont_input_range.upper.min && value <= discont_input_range.upper.max) {
    value = map(value,
                this->discont_input_range.upper.min,
                this->discont_input_range.upper.max,
                this->discont_output_range.upper.min,
                this->discont_output_range.upper.max);    
  } else {
    // maybe find the closest boundary?
    int delta_low = abs(this->discont_input_range.lower.min - value);
    int delta_high = abs(this->discont_input_range.upper.max - value);
    if ( delta_low <= delta_high) {
      value = this->discont_output_range.lower.min;
    } else {
      value = this->discont_output_range.upper.max;
    }
    
  }

  return value;
}

// Dispatches the current reading for this dimension.
void sensor::Orientation::Dimension::send() {
  (*this.*dispatcher)();
}

void sensor::Orientation::Dimension::debug_dispatcher() {
  Serial.print("  ");
  Serial.print(this->v);
  Serial.println("");
}

void sensor::Orientation::Dimension::midi_cc_dispatcher() {
  if (!this->debounce(this->v)) {
    this->midi_interface->sendControlChange(this->midi_cc_number, this->v, this->midi_channel);
  }
}
