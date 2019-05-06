#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include "orientation.h"
#include "sensor.h"


sensor::Orientation::Orientation(midi::MidiInterface<HardwareSerial>* midi_interface,
                                 sensor::range_t input_range,
                                 sensor::range_t output_range,
                                 bool invert_values,
                                 bool debug)
  : Adafruit_BNO055(55),
    sensor::Sensor(midi_interface,
                   input_range,
                   output_range,
                   invert_values,
                   debug)
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
}

// read gets the current values of the x, y, z orientation and
// populates the x, y, z attributes of this object.
void sensor::Orientation::read() {
  sensors_event_t event;
  this->getEvent(&event);

  this->x = event.orientation.x;
  this->y = event.orientation.y;
  this->z = event.orientation.z;
}

void sensor::Orientation::send() {
  //this->dispatch;
}
