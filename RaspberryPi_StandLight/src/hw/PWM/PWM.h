#ifndef PWM_H
#define PWM_H
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

class PWM
{
private:
     int pinNumber;
     int low;
     int high;
public:
    PWM(int pin, int min, int max);
    virtual ~PWM();
    void Stopmotor();
    void startmotor(int speed);
    int Pin;
};

#endif

