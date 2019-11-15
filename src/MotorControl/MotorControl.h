#ifndef THANADOL_HELPER_MOTOR_CONTROL_H
#define THANADOL_HELPER_MOTOR_CONTROL_H

#include<Arduino.h>
#include<Pin.h>

class MotorControl 
{
private:
    Pin enable;
    Pin in1;
    Pin in2;
    int calibration_offset;  // actual power = code power + calibration_offset
public:
    bool inverse;

    MotorControl(Pin enable, Pin in1, Pin in2, bool inverse=false, int calibration_offset=0);
    ~MotorControl();

    void setSpeedPWD(int speed);
    void setSpeedPercentage(int speed_percentage);
    void setSpeedRatio(float speed_ratio);

    void setCalibration(int offset) {
        this->calibration_offset = offset;
    }

    void setCalibrationPercentage(int offset) {
        this->calibration_offset = (255 * offset) / 100;
    }

    void stop();

    bool isInverse();
    void setInverse(bool inverse);
    void toggleInverse();
};

// TODO: change serial to optional
MotorControl::MotorControl(Pin enable, Pin in1, Pin in2, bool inverse, int calibration_offset): 
    enable(enable),
    in1(in1),
    in2(in2),
    inverse(inverse),
    calibration_offset(calibration_offset)
{   
    this->in1.setOutputLow();
    this->in2.setOutputLow();

    #ifdef THANADOL_HELPER_SERIAL_DEBUG
    if(Serial && !digitalPinHasPWM(enable.getNumber())) {
        char str[65];
        sprintf(str, "WARNING: Pin %d doesn't have pwm but the software expected it", enable.getNumber());
        Serial.println(str);
    }
    #endif
}

MotorControl::~MotorControl() {}

/// set motor speed (0 -> 255)
void MotorControl::setSpeedPWD(int speed) 
{
    speed = inverse ? -speed : speed;
    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        in1.setHigh();
        in2.setLow();
        this->enable.setDutyCycle(speed + calibration_offset);
    }
    else if (speed < 0) {
        in1.setLow();
        in2.setHigh();
        this->enable.setDutyCycle(-(speed + calibration_offset));
    }
    else {
        in1.setLow();
        in2.setLow();
        this->enable.setDutyCycle(0);
    }
}

/// set motor speed as percentage (0 -> 100)
void MotorControl::setSpeedPercentage(int percentage)
{
    this->setSpeedPWD((255 * percentage) / 100);
}

/// set motor speed as ratio (0.0 -> 1.0)
void MotorControl::setSpeedRatio(float ratio) {
    this->setSpeedPWD((int)(ratio * 255.0f));
}

void MotorControl::stop() {
    this->setSpeedPWD(0);
}

bool MotorControl::isInverse() { return this->inverse; }
void MotorControl::setInverse(bool inverse) { this->inverse = inverse; }
void MotorControl::toggleInverse() { this->inverse = !this->inverse; };

#endif