#ifndef THANADOL_HELPER_PID_H
#define THANADOL_HELPER_PID_H

#include<Arduino.h>

namespace Helper {
    class SimplePID {
    private:
    double prevErr = 0.0;
    double integral = 0.0;
    public:
    double Kp, Ki, Kd;
    bool integralAccumulation = true;
    
    SimplePID(double Kp, double Ki, double Kd) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
    }
    
    double feedbackViaErr(double error, double dt) {
        if(this->integralAccumulation) {
            this->integral += error * dt;
        }
        double derivative = (error - prevErr) / dt;
        prevErr = error;
        
        return Kp * error + Ki * integral + Kd * derivative;
    }
    
    double feedback(double measured, double setpoint, double dt) {
        double error = setpoint - measured;
        return this->feedbackViaErr(error, dt);
    }
    
    void reset() {
        this->prevErr = 0.0;
        this->integral = 0.0;
    }
    };
}
#endif