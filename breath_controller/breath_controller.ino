#include <MIDI.h>

// setup midi library
MIDI_CREATE_DEFAULT_INSTANCE();

int intensity = 0;
int last = 0;
int reading;
int sensorIni;

const int analogInPin = A0;

// set pins for distance sensor
const int trigPin = 8;
const int echoPin = 7;
long duration;
int distance;
int amplitude;
int previous = 0;

void setup() {
 MIDI.begin(); 
    // set distance sensor pin modes
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //Read of the initial pressure sensor value (not blowing) for calibration
    delay(200);
    sensorIni = analogRead(analogInPin);
}

void loop() {
        reading = constrain(analogRead(analogInPin)-sensorIni, 0, 1014-sensorIni);
        intensity = map(reading, 0, 1014-sensorIni, 0, 127);

        //Only sending if value has changed from last time and is different from 0 to prevent saturation
        if(intensity > 0 && intensity != last){
          MIDI.sendControlChange(2, intensity, 1);
          last = intensity;
        }

        //If intensity drops to 0 from another value the 0 isn't sent and the last value is maintained, so we send a 0
        else{
          if(intensity == 0 && last > 0){
            MIDI.sendControlChange(2, 0, 1);
            last = 0;
          }
        }

        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance in centimeters
        distance= duration*0.034/2;
        // convert the distance to a midi control value
        amplitude = map(constrain(distance, 0, 50), 0, 50, 0, 127);

                //Only sending if value has changed from last time and is different from 0 to prevent saturation
        if(amplitude > 0 && amplitude != previous){
          MIDI.sendControlChange(1, amplitude, 1);
          previous = amplitude;
        }

        //If intensity drops to 0 from another value the 0 isn't sent and the last value is maintained, so we send a 0
        else{
          if(amplitude == 0 && previous > 0){
            MIDI.sendControlChange(1, 0, 1);
            previous = 0;
          }
        }
}
