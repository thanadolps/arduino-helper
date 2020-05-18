# arduino-helper
Some arduino helper class for use in arduino project

## Prerequisite
Require [Pin](https://github.com/fenichelar/Pin) arduino library

## Installtion

copy *arduino_helper* folder into your project and use `#include "arduino_helper/prelude.h"`


## List of classes
* [`MotorControl`](arduino_helper/MotorControl) for controling motor with *H-Bridge Dual Motor Controller*
* [`FiveLightSensor`](arduino_helper/FiveLightSensor) for controlling light sensor with 5 input pin
* [`SerialIO`](arduino_helper/SerialIO) for reciving/sending data from/to serial
* [`PID`](arduino_helper/PID) for functionality of simple pid controller
* [`SevenSegment`](arduino_helper/SevenSegment) for outputing to 7-segment through 8-bit shift registry
* [`Button`](arduino_helper/Button) for ingredient for complex button signaling

## Flag
`#define THANADOL_HELPER_SERIAL_DEBUG` enable some function to print out information/warning via `Serial` object, it can interfere with hardware serial so it's disable by default 

## License
[MIT](LICENSE)