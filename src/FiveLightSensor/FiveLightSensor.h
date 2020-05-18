#ifndef THANADOL_HELPER_FIVE_SENSOR_H
#define THANADOL_HELPER_FIVE_SENSOR_H

#include <Arduino.h>
#include <Pin.h>

namespace Helper {
    class FiveLightSensor
    {
    public:
        Pin sensors[5];

        FiveLightSensor(Pin in1, Pin in2, Pin in3, Pin in4, Pin in5);
        ~FiveLightSensor();

        #ifdef THANADOL_HELPER_SERIAL_DEBUG
        void serialPrint();
        #endif

        Pin r1_pin() { return this->sensors[3]; }
        Pin r2_pin() { return this->sensors[4]; }
        Pin l1_pin() { return this->sensors[1]; }
        Pin l2_pin() { return this->sensors[0]; }
        Pin mid_pin() { return this->sensors[2]; }

        bool r1() {return this->r1_pin().getValue();}
        bool r2() {return this->r2_pin().getValue();}
        bool l1() {return this->l1_pin().getValue();}
        bool l2() {return this->l2_pin().getValue();}
        bool mid() {return this->mid_pin().getValue();}

        bool all_right() {return this->r1() && this->r2(); }
        bool all_left() {return this->l1() && this->l2(); }

        bool any_right() {return this->r1() || this->r2(); }
        bool any_left() {return this->l1() || this->l2(); }

        bool match(bool l2, bool l1, bool mid, bool r1, bool r2) {
            return 
                this->r1() == r1 &&
                this->r2() == r2 &&
                this->l1() == l1 && 
                this->l2() == l2 && 
                this->mid() == mid;
        }
    };

    FiveLightSensor::FiveLightSensor(Pin in1, Pin in2, Pin in3, Pin in4, Pin in5)
    {
        this->sensors[0] = in1;
        this->sensors[1] = in2;
        this->sensors[2] = in3;
        this->sensors[3] = in4;
        this->sensors[4] = in5;

        for(auto sensor : sensors) {
            sensor.setInput();
        }
    }


    #ifdef THANADOL_HELPER_SERIAL_DEBUG
    void FiveLightSensor::serialPrint() {
        for(auto sensor : sensors) {
            Serial.print(sensor.getValue());
            Serial.print(' ');
        }
        Serial.println();
    }
    #endif

    FiveLightSensor::~FiveLightSensor()
    {
    }

}

#endif