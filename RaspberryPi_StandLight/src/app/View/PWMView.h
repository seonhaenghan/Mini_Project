#ifndef PWMVIEW_H
#define PWMVIEW_H
#include "PWM.h"
#include "MotorPowerState.h"
class PWMView
{
private:
    PWM *pwm;
    int powermode;
    int tempsign;
public:
    PWMView(PWM *pwm);
    ~PWMView();
    void tempState(int tempOver);
    void powerState(int motor_power);
    
};

#endif