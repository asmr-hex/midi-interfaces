# Interface Ideas
### interesting sensors
* vibration sensors -[slow](https://www.adafruit.com/product/1767), [medium](https://www.adafruit.com/product/2384), [fast](https://www.adafruit.com/product/1766)
* [force-sensitive resistor](https://www.adafruit.com/product/166)
* [rotary encoder](https://www.adafruit.com/product/377)
* flex sensors - [long](https://www.adafruit.com/product/182) and [short](https://www.adafruit.com/product/1070)
* [capacitive touch sensors](https://www.adafruit.com/product/1982)
* [resistive touch screen](https://www.adafruit.com/product/333)
* [distance sensor](https://www.adafruit.com/product/3942)
* [piezo pickup](https://www.adafruit.com/product/1739)
* [absolute orientation](https://www.adafruit.com/product/2472)
* [velostat](https://www.adafruit.com/product/1361) - conductive sheet
* [conductive Rubber Cord](https://www.adafruit.com/product/519)
* [conductive thread](https://www.adafruit.com/product/640)

### musical interface design
* [Musical Interface Technology Design](https://pdfs.semanticscholar.org/e6ac/bf5c895307678af04bb30cd91ed63b409588.pdf)
  * interfaces for music therapy
  * deterministic behavior is desireable
* [Human Computer Interaction And Musical Instruments](https://hal.inria.fr/hal-01370588/document)

### Glove Controller
#### overview
* use hand orientation (X/Y/Z) and angular velocity to control expression
* use bended fingers to control note on/off/duration?
* tapping tips of fingers controls note on/off/duration?
* control box to change play modes
#### sensors
* flex sensors on fingers of gloves
* orientation sensor on back on hands
* force sensors on finger tips (velostat with conductive thread)
#### proof of concept bill of materials
* short flex sensors (5)
* orientation sensor (1)
* conductive thread (1 spool)
* velostat (one sheet)
* arduino uno R3 (1)
* rotary encoder (2)
* gloves
