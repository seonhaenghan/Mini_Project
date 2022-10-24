#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>
#include "Led.h"
#include "LightState.h"
#include "LCD.h"

// 상태 선언 
class View
{
private:
    int lightState;
    Led *light1;
    Led *light2;
    Led *light3;
    Led *light4;
    Led *light5;
    LCD *lcd;
    
public:
    View(Led *led1,Led *led2,Led *led3,Led *led4,Led *led5, LCD *Lcd);    // 생성자
    virtual ~View();                                            // 소멸자 
    void setState(int state);                                
    void lightView();
    void lightOn_1();
    void lightOn_2();
    void lightOn_3();
    void lightOn_4();
    void lightOn_5();
    void lightOff();
    void tempEvent(float temp);
};

#endif /* __VIEW_H__ */