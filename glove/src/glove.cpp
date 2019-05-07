#include <Arduino.h>
#include <MIDI.h>
#include "glove.h"
#include "config.h"
#include "sensors/flex.h"
#include "sensors/orientation.h"
#include "sensors/sensor.h"


Glove::Glove(Config config)
  : config(config)
{
  // instantiate a new midi interface
  midi_interface = new midi::MidiInterface<HardwareSerial>((HardwareSerial&)Serial);

  // TODO (coco|5.4.2019) incorporate this into config
  byte pins[] = {A0, A1, A2, A3, A4};
  sensor::range_t finger_calibrations[5] = {
                                            {99, 242},
                                            {125, 245},
                                            {146, 287},
                                            {189, 254},
                                            {149, 300},
  };
  int finger_cc_numbers[5] = {1,2,11,12,13};
  
  // initialize finger flex sensors
  size_t n = sizeof(fingers)/sizeof(fingers[0]);
  for (byte i = 0; i < n; i++) {
    fingers[i] = new sensor::Flex(pins[i],
                                  midi_interface,
                                  sensor::Flex::DispatcherType::MidiControlChange,
                                  finger_calibrations[i],
                                  {0, 127},
                                  false,
                                  true);
    fingers[i]->set_midi_cc_number(finger_cc_numbers[i]);
  }

  // initialize orientation sensor
  // orientation = new sensor::Orientation();
}

void Glove::setup() {
  if ( this->config.debug ) {
    // start serial communication
    Serial.begin(9600);
  } else {
    // start midi interface
    this->midi_interface->begin();
  }

  // calibrate fingers
  // this->calibrate(10);
}

void Glove::calibrate(int seconds) {
  int timesteps = (seconds * 1000) / this->dt;
  int split_timesteps = timesteps / 2;

  Serial.print("Open your fist to calibrate finger sensors in ");
  for (int i=3; i>0; i--) {
    Serial.print(i);
    Serial.print("...");

    delay(1000);
  }
  Serial.print("CALIBRATING OPEN FIST");
  
  // calibrate upperbound
  for (int t=0; t < split_timesteps; t++) {
    for (sensor::Flex *finger : this->fingers) {
      finger->calibrate(sensor::CalibrateUpperBound);
    }

    Serial.print(".");
    delay(this->dt);
  }

  Serial.println("Success!");

  Serial.print("Close your fist to calibrate finger sensors in ");
  for (int i=3; i>0; i--) {
    Serial.print(i);
    Serial.print("...");

    delay(1000);
  }
  Serial.print("CALIBRATING CLOSED FIST");
  
  // calibrate lowerbound
  for (int t=0; t < split_timesteps; t++) {
    for (sensor::Flex *finger : this->fingers) {
      finger->calibrate(sensor::CalibrateLowerBound);
    }

    Serial.print(".");
    delay(this->dt);
  }

  Serial.println("Success!");

  Serial.println("");
  Serial.println("====================== Calibrated Bounds ======================");
  for (sensor::Flex *finger : this->fingers) {
    Serial.print(finger->pin - 54);
    Serial.print(":    { ");
    Serial.print(finger->input_range.min);
    Serial.print("   ");
    Serial.print(finger->input_range.max);
    Serial.println(" }");
  }
  Serial.println("===============================================================");
  Serial.println("");

  delay(3000);
}

// read all the connected sensors
void Glove::read_and_dispatch() {
  // read from finger sensors and send messages
  for (sensor::Flex *finger : this->fingers) {
    finger->read();
    finger->send();
  }

  Serial.println("");

  delay(this->dt);

  // read orientation sensor and send messages
  // this->orientation.read();
  // this->orientation.send();
}
