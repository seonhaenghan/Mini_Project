#ifndef TIMERSERVICE_H
#define TIMERSERVICE_H
#include <string>
#include "TimerView.h"

class TimerService
{
private:
    TimerView *timerView;
    

public:
    TimerService(TimerView *timerView);
    virtual ~TimerService();
    void updateEvent(std::string strbtn);
    void timercounter(int timercount);
};

#endif