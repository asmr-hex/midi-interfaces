#include <Arduino.h>
#include "orientation.h"


//bool DEBUG = true;

OrientationSensor::OrientationSensor() : Adafruit_BNO055(55) {
  // in order to proceed, we must wait until the orientation sensor has been detected.
  if ( !this->begin() && true ) {
    Serial.print("Yikes! BNO055 sensor was not detected...check your wiring or I2C ADDR!");
    while(1);
  }

  // great, it should have connected at this point

  delay(1000);

  // set the sensor to use an external clock (Arduino clock)
  this->setExtCrystalUse(true);
}

