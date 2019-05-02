#ifndef ORIENTATION_SENSOR_H_
#define ORIENTATION_SENSOR_H_

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>

// struct Threshold {
//   int min;
//   int max;
// };

class OrientationSensor : public Adafruit_BNO055 {
public:
  OrientationSensor();
};

#endif
