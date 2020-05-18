#ifndef THANADOL_HELPER_SEVEN_SEGMENT_H
#define THANADOL_HELPER_SEVEN_SEGMENT_H

#include<Arduino.h>

namespace Helper {
    class SevenSegment {
    private:	
    const int HEX_DIGIT_7SEG[16] ={
        0x3F,
        0x06,
        0x5B,
        0x4F,
        0x66,
        0x6D,
        0x7D,
        0x07,
        0x7F,
        0x6F,
        0x77,
        0x7C,
        0x39,
        0x5E,
        0x79,
        0x71
    };
    
    int dataPin;
    int clockPin;
    int latchPin;
    public:
    SevenSegment(int dataPin, int clockPin, int latchPin) {
        this->dataPin = dataPin;
        this->clockPin = clockPin;
        this->latchPin = latchPin;
        
        pinMode(dataPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(latchPin, OUTPUT);
    }
    
    void setByte(u8 byte) {
        shiftOut(this->dataPin, this->clockPin, MSBFIRST, byte);
        digitalWrite(this->latchPin, HIGH);
        digitalWrite(this->latchPin, LOW);
    }
    
    void setHex(int hex) {
        this->setByte(HEX_DIGIT_7SEG[hex % 16]);
    }
    };
}

#endif