#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include "LCD.h"

class TimerView
{
private:
    LCD *lcd;
    int display;
public:
    TimerView(LCD *lcd);
    virtual ~TimerView();
    void updateTime(int hour,int min,int sec);
    void timermode(int mode);
};

#endif