# midi-interfaces
notes and implementations of some midi interfaces

# Arduino Uno (R3) Midi Device Notes
### background
* main processor on Arduino Uno, ATmega328P, can't speak USB.
* so, a second processor, ATmega16U2, (the square IC between the USB port and Tx/Rx LEDS) is programmed as a USB-Serial translator.
* by default, the ATmega16U2 is flashed with firmware to allow you to load your Arduino Sketches from your laptop.
* since we want out Arduino to be recognized as a USB-MIDI device, we need to re-flash it with new firmware (see below).

### dependencies
* `dfu-programmer` - commandline tool to flash firmware onto a variety of chips (`brew install dfu-programmer` on OSX)
* `hiduino` - contains the new firmware to change our arduino into a USB-MIDI device (`git clone git@github.com:ddiakopoulos/hiduino.git`)
* [`MIDIUSB`](https://www.arduino.cc/en/Reference/MIDIUSB) - Arduino library for MIDI (download via Arduino package manager)

### steps
* make sure the arduino is in DFU mode if you need to flash [see this pic](http://arduino.cc/en/uploads/Hacking/Uno-front-DFU-reset.png)
* make sure default arduino usbserial firmware is flashed on ATmega16U2
* write sketch
* load sketch onto Arduino
* flash ATmega16U2 with `hiduino` firmware
* unplug/replug
* test and repeat
_this process is automated in the included cli tool `arduinoctl`_

### etc
* the `hiduino` repo contains the new midi firmware `hiduino/compiled_firmwares/arduino_midi.hex`
* to reflash the default arduino firmware, clone the [Arduino AVR Cores repo](https://github.com/arduino/ArduinoCore-avr) and use `/ArduinoCore-avr/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-uno.hex`
* since the new midi firmware can't support loading sketches, we need to reflash the default arduino firmware each time we want to load a new sketch.

### troubleshooting
* remember to always unplug/replug in after flashing
* if you get `dfu-programmer: no device present.` you need to set the arduino to DFU mode.

# Glove
### resources
* [attach multiple BNO055 Sensors to one arduino 1](https://forums.adafruit.com/viewtopic.php?f=25&t=84929#p538623)
* [attach multiple BNO055 Sensors to one arduino 2](https://forum.arduino.cc/index.php?topic=365597.msg2554732#msg2554732)
