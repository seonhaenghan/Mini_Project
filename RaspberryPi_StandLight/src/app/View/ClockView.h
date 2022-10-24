#ifndef CLOCKVIEW_H
#define CLOCKVIEW_H

#include <time.h>
#include "LCD.h"

class ClockView
{
private:
    struct tm timeDate;
    LCD *lcd;
public:
    ClockView(LCD *Lcd);
    virtual ~ClockView();
    void updateTime(struct tm *timeData, int mode);
};

#endif