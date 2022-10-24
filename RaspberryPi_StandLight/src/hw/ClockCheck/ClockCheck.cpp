#include "ClockCheck.h"

ClockCheck::ClockCheck()
{
    prevSec = 0; 
}

ClockCheck::~ClockCheck()
{

}

bool ClockCheck::isUpdate()
{
    time_t curSec = time(NULL); // 현재 시간을 읽어온다. 
    if(curSec == prevSec)
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}