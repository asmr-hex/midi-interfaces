#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <MIDI.h>
#include "src/sensors/orientation.h"


bool DEBUG = true;
OrientationSensor *orientationSensor;

// initialize default midi instance
MIDI_CREATE_DEFAULT_INSTANCE();

/* Adafruit_BNO055 newOrientationSensor() { */
/*   // create new sensor instance */
/*   Adafruit_BNO055 sensor = Adafruit_BNO055(55); */

/*   // initialize the sensor */
/*   if ( !sensor.begin() && DEBUG ) { */
/*     Serial.print("Oh No! BNO055 sensor was not detected...check your wiring or I2C ADDR! ;D"); */
/*     while(1); */
/*   } */

/*   // wait for a second. */
/*   delay(1000); */

/*   // set sensor to use an external clock (Arduino clock) */
/*   sensor.setExtCrystalUse(true); */

/*   return sensor; */
/* } */

void setup() {
  if ( !DEBUG ) {
    // in non-test situations, this microcontroller communicates via MIDI
    MIDI.begin();
  } else {
    // in testing situations, we communicate via serial
    Serial.begin(9600);
  }

  orientationSensor = new OrientationSensor();
}

int last = 0;
int thresh = 3;//30;
int maxInput = 270;
int minInput = 110;
int maxOutput = 127;//10000;

void loop() {

  /* Get a new sensor event */ 
  sensors_event_t event; 
  orientationSensor->getEvent(&event);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);

  int rawInputs[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};
  int idx = 0;
  for (const int rawInput : rawInputs) {
    int reading = constrain(rawInput, minInput, maxInput);
    int v = map((maxInput - reading) + minInput, minInput, maxInput, 0, maxOutput);
    Serial.print("\t");
    Serial.print(idx);
    Serial.print(": ");
    Serial.print(rawInput);
//    if (v >= lasts[idx] + thresh || v <= lasts[idx] - thresh) {
//      Serial.println(v);
//      last = v;
//    }
    idx++;
  }

  Serial.println("");
  delay(500);
  
//  int reading = constrain(analogRead(A0), minInput, maxInput);
//  int v = map((maxInput - reading) + minInput, minInput, maxInput, 0, maxOutput);
//  
//  if (v >= last + thresh || v <= last - thresh) {
//    Serial.println(v);
//    // MIDI.sendPitchBend(v, 1);
//    last = v;
//  }

//  int r = constrain(analogRead(A0), 150, 350);
//  int V = map((350 - r) + 150, 150, 350, 0, 127);
//  if (V >= last + 3 || V <= last - 3) {
//    Serial.println(V);
//    last = V;
//  }

}
