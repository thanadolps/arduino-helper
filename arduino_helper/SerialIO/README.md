# Serial IO
Class for reciving/sending data from/to serial

## Motivation
While Arduino's Serial already have many good function with string, it still lacking when sending a number.

One way to send a number is converting number to string, send the string and then parse it back to number. but while it's easy to setup with Arduino's serial, it's expensive on both memory and time. 

Another way is to send the number as byte which is significantly cheaper than previous method but require operation on byte which is harder to setup.

In order to fix that, Serial IO provide a helper function for reading/writing number from serial directly from byte. make sending number both easy and quick

## Function
All of `SerialIO` method are static and require Serial object pointer in first argument.

The list is show for i8, but similary method for i16 exist. (i32, i64) are planed but not yet implement
* `SerialIO::read_i8`: read bytes from serial and return it as i8, can fail if serial don't contains enough byte
* `SerialIO::wait_to_read_i8`: wait for serial to contain enough byte then do `SerialIO::read_i8`

## Example
```cpp
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "arduino_helper/lib.h"


auto bluetooth_serial = SoftwareSerial(2, 3);

void setup()
{
    bluetooth_serial.begin(9600);
    Serial.begin(9600);

    // wait until reciving inital message from bluetooth
    int8_t inital_msg =  bluetooth_serial.wait_to_read_i8(&bluetooth_serial);

    Serial.println("Recived Inital Message");
}

void loop()
{
    // wait to reciving i16
    int16_t num = SerialIO::wait_to_read_i16(&bluetooth_serial);

    Serial.println("Recived number: ");
    Serial.print(num);
}

```