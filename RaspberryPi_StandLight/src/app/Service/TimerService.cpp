#include "TimerService.h"

TimerService::TimerService(TimerView *timerView)
{
    this->timerView = timerView;
    
}

TimerService::~TimerService()
{
}

void TimerService::updateEvent(std::string strbtn)
{// 누를 시 Display 되도록 해야함 
    static int mode = 0; 
    if(strbtn == "timerButton")
    {
        mode++;
        mode %= 2; 
        timerView->timermode(mode);
    }
}

void TimerService::timercounter(int timercount)
{
    int hour = timercount / 3600 % 24;
    int min = timercount / 60 % 60;
    int sec = timercount % 60;

    timerView->updateTime(hour, min, sec);
}