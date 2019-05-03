#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "orientation.h"
#include "config.h"


sensor::Orientation::Orientation(sensor::Config config)
  : Adafruit_BNO055(55), config(config)
{
  // in order to proceed, we must wait until the orientation sensor has been detected.
  if ( !this->begin() && this->config.debug ) {
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
