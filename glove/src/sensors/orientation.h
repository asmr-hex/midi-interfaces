#ifndef ORIENTATION_SENSOR_H_
#define ORIENTATION_SENSOR_H_

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include "config.h"


namespace sensor {
  
  class Orientation : public Adafruit_BNO055 {
  public:
    
    Orientation(sensor::Config config = {});
    void read();

    sensor::Config config;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };
  
}

#endif
