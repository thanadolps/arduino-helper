#ifndef THANADOL_HELPER_BUTTON_H
#define THANADOL_HELPER_BUTTON_H

#include<Arduino.h>

namespace Helper {
    class Button {
    private:
        int pin;
    public:
        
        Button(int pin) {
            this->pin = pin;
            pinMode(pin, INPUT_PULLUP);
        }
        
        bool checkPressed(){
            return !digitalRead(this->pin);
        }
    };

    class PluseButton: public Button {
    private:
        typedef Button super;
        bool justPressed = false;
    public:
        PluseButton(int pin) : super(pin) {
            this->justPressed = false;
        }
        
        bool checkPressed() {
            bool press = super::checkPressed();
            this->justPressed = press;
            return press;
        }
        
        bool checkRising() {
            bool prev = this->justPressed;
            bool now = checkPressed();
            return !prev && now;
        }
    };
}

#endif