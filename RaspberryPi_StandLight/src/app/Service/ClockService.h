#ifndef CLOCKSERVICE_H
#define CLOCKSERVICE_H

#include <time.h>
#include "ClockView.h"
class ClockService
{
private:
    time_t curTime;
    ClockView *clockView;
    int mode;
public:
    ClockService(ClockView *view);
    virtual ~ClockService();
    void updateEvent();
    void updatestate(std::string strbtn);
};

#endif