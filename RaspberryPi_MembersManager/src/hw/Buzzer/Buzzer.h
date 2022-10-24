#ifndef BUZZER_H
#define BUZZER_H

#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

class Buzzer
{
private:
     int pinNumber;
     int low;
     int high;
public:
    Buzzer(int pin, int min, int max);
    virtual ~Buzzer();
    void stopBuzzer();
    void startBuzzer(int value);
    int Pin;
};

#endif