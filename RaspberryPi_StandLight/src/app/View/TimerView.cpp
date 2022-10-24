#include "TimerView.h"

TimerView::TimerView(LCD *lcd)
{
	this->lcd = lcd;
	display = 0;
}

TimerView::~TimerView()
{

}

void TimerView::timermode(int mode)
{// 버튼이 눌러져 1일 때 lcd에 출력 
	display = mode;
}

void TimerView::updateTime(int hour, int min, int sec)
{
	if (display)
	{
		char buff[30];
		sprintf(buff, "%02d:%02d:%02d   ", hour, min, sec);
		lcd->WriteStringXY(1, 0, buff);
		
	}
	
}