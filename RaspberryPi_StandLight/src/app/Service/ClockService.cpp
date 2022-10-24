#include "ClockService.h"
#include <string>
ClockService::ClockService(ClockView *view)
{
    curTime = 0;
    clockView = view; 
    mode = 0;
}

ClockService::~ClockService()
{

}

void ClockService::updateEvent()
{
    
    curTime = time(NULL); 
    // time(NULL); >> return 값으로 70년 대 부터 1sec씩 Count
    struct tm *timeDate = localtime(&curTime);
    clockView->updateTime(timeDate, mode);
}
void ClockService::updatestate(std::string strbtn)
{
    static int onoffmode = 0; 
    if(strbtn == "timerButton")
    {
        onoffmode++;
        onoffmode %= 2;
        mode = onoffmode;
    }
    

    
    
}