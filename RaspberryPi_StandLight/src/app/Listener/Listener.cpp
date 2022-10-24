#include "Listener.h"
#include <wiringPi.h>
Listener::Listener(Button *modebutton,Button *powerbutton, Controller *control,
    Button *windpowerButton,  Button *timerButton,
     ClockCheck *clock, DHT11 *dht11, UltraSonic *Ultrasonic)
{
    this->modeButton = modebutton;
    this->powerButton = powerbutton;
    this->windpowerButton = windpowerButton;
    this->timerButton = timerButton;
    this->controller = control;
    this->clockcheck = clock;
    this->dht11 = dht11;
    this->Ultrasonic = Ultrasonic;
    //this-> (Class에서 선언한 변수), this가 없는 것은 함수 매개변수 
}

Listener::~Listener()
{
}

void Listener::checkEvent()
{
    if (modeButton->getState() == RELEASE_ACTIVE)
    {// Button이 눌러졌을 때 modeButton이 Controller로 전송 됨
        controller->updateEvent("modeButton");
    }

    if(clockcheck->isUpdate())
    {// clock이 들어오는 경우 clockUpdate로 알려준다. >> Controller에 알려줌 
        controller->updateEvent("clockUpdate");
    }

    if (powerButton->getState() == RELEASE_ACTIVE)
    {// Button2가 눌러졌을 때 modeButton이 Controller로 전송 됨
        controller->updateEvent("powerButton");
       
    }
    if (windpowerButton -> getState() == RELEASE_ACTIVE)
    {
        controller->updateEvent("windpowerButton");
    }
    if (timerButton -> getState() == RELEASE_ACTIVE)
    {
        controller->updateEvent("timerButton");
    }

    DHT_Data dhtData = dht11->readData();
    if(!dhtData.error)
    {
        controller->updateTempHumid(dhtData); 
    }

    static uint32_t prevTime = 0;
    if (millis() - prevTime > 2000)
    {
        prevTime = millis();
        DHT_Data dhtData = dht11->readData();
        if(!dhtData.error)
        {
            controller->updateTempHumid(dhtData);
        }
    }
    // 1초 간격으로 controller에 data를 전달함 
    static uint32_t prevUltraSonicTime = 0;
    if (millis() - prevUltraSonicTime > 1000)
    {
        prevUltraSonicTime = millis();
        int distance = Ultrasonic->readDistance();
        controller->updateDistance(distance);
    }

    static uint32_t time = 0;
    static uint32_t timerCount = 0;
    if (millis() - time > 1000)
    {// 1초 마다 실행 
        time = millis();
        timerCount++;
        if(powerButton->getState() == RELEASE_ACTIVE)
        {// 전원을 껏을 때 0으로 초기화 
            timerCount = 0;
        }
        controller->updateTimer(timerCount);
    }
}