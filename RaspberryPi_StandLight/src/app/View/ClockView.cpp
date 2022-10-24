#include "ClockView.h"
#include <iostream>
ClockView::ClockView(LCD *Lcd)
{
    this->lcd = Lcd; 
    //timeDate = 0; Error 발생으로 주석처리 
}

ClockView::~ClockView()
{

}


//ClockService에서 넘어온 값 
void ClockView::updateTime(struct tm *timeData, int mode)
{
    if(mode == 0)
    {
        char buff[30];
        sprintf(buff, "%02d:%02d:%02d  ", 
        timeData->tm_hour, timeData->tm_min, timeData->tm_sec);

        lcd->WriteStringXY(1, 0, buff);
    }
    
}

// View에서 값을 넘겨 받음

