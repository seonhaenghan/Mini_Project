#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H
#include "State.h"
#include "LCD.h"

class DisplayView
{
private:
    LCD *lcd;
public:
    DisplayView(LCD *lcd);
    virtual ~DisplayView();
    void displayMode(int mode);
};

#endif