# arduino-helper
Some arduino helper class for use in arduino project

## Prerequisite
Require [Pin](https://github.com/fenichelar/Pin) arduino library

## Installtion

copy *arduino_helper* folder into your project and use `#include "arduino_helper/lib.h"`


## List of classes
* [`MotorControl`](arduino_helper/MotorControl.h) for controling motor with *H-Bridge Dual Motor Controller*
* [`FiveLightSensor`](arduino_helper/FiveLightSensor.h) for controlling light sensor with 5 pin
* [`SerialIO`](arduino_helper/SerialIO.h) for reciving/sending data from/to software/hardware serial

## Flag
`#define THANADOL_HELPER_SERIAL_DEBUG` enable some function to print out information/warning via `Serial` object, it can interfere with hardware serial so it's disable by default 

## License
[MIT](LICENSE)