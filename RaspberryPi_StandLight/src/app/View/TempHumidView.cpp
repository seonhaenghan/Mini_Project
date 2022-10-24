#include "TempHumidView.h"

TempHumidView::TempHumidView(LCD *lcd)
{
    this->lcd = lcd;
}

TempHumidView::~TempHumidView()
{

}

void TempHumidView::setTempHumidData(float temp, float humid)
{
    if(temp >= 28)
    {
        char buff1[30];
        sprintf(buff1, "%.1fC", temp);
        lcd->WriteStringXY(0, 11, buff1);
        
        char buff2[30];
        sprintf(buff2, "warning%c", '!');
        lcd->WriteStringXY(1, 8, buff2);
       // printf("%s %s\n",buff1, buff2);
    }
    else
    {
        char buff1[30];
        sprintf(buff1, "%.1fC", temp);
        lcd->WriteStringXY(0, 11, buff1);
        

        char buff2[30];
        sprintf(buff2, " %.1f%c", humid, '%');
        lcd->WriteStringXY(1, 10, buff2);
        //printf("%s %s\n",buff1, buff2);
    }
    
}

