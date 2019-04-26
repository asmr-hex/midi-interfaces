#include <MIDI.h>

// setup midi library
MIDI_CREATE_DEFAULT_INSTANCE();


void setup() {
  MIDI.begin(); 
  //Serial.begin(9600);
}

int last = 0;
int thresh = 30;
int maxInput = 270;
int minInput = 110;

void loop() {

  int reading = constrain(analogRead(A0), minInput, maxInput);
  int v = map((maxInput - reading) + minInput, minInput, maxInput, 0, 10000);
  
  if (v >= last + thresh || v <= last - thresh) {
    //Serial.println(v);
    MIDI.sendPitchBend(v, 1);
    last = v;
  }

  /*
  int v1 = analogRead(A1);
  Serial.println(v1);
  
  int v2 = analogRead(A2);
  Serial.println(v2);
  
  int v3 = analogRead(A3);
  Serial.println(v3);
  
  int v4 = analogRead(A4);
  Serial.println(v4);
  */
}
