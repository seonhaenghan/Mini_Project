#include "Controller.h"
#include "LightState.h"
Controller::Controller(Service *serv, ClockService *clockServ, 
    TempHumidService *temphumidService, PWMService *pwmService, TimerService *timerService)
{
    service = serv; // Service에 대한 주소를 갖는다. 
    clockService = clockServ; 
    lightState = LIGHT_OFF;
    this->temphumidService = temphumidService; 
    this->pwmService = pwmService;
    this->timerService = timerService;
}
Controller::~Controller() // 소멸자 
{

}
void Controller::updateEvent(std::string strBtn)
{
    // 각 Service에 String을 전송해 Button Event 여부를 알려줄거임
    if (strBtn == "modeButton") 
    {
        //StandLight mode
        service->updateState("modeButton");
    }   

    if (strBtn == "powerButton") 
    {
        //StandLight Power on/off
        service->updateState("powerButton");
    }  

    if (strBtn == "clockUpdate") 
    {
        // Real time data 전송으로 함수를 실행만 시킴 
        clockService->updateEvent();
    }  

    if (strBtn == "windpowerButton") 
    {
        // Button이 눌릴 때마다 Str 전송 
        pwmService->updateState("windpowerButton");
    } 
    // timer Display Button
    if (strBtn == "timerButton") 
    {
        timerService->updateEvent("timerButton");
        // Timer가 Display 될 때 Clock이 Display 되면 안됨
        // 그래서 동시에 신호를 보낸다. 
        clockService->updatestate("timerButton");
    }  
}

void Controller::updateTimer(int timer)
{
    timerService->timercounter(timer);
}


void Controller::updateTempHumid(DHT_Data dhtData)
{
    // 온도 정보를 전달할 예정임 
    temphumidService->upDateEvent(dhtData);
    service->upDateEvent(dhtData);
    pwmService->upDatetemp(dhtData);
}

void Controller::updateDistance(int distance)
{
    //측정된 거리 값을 Service에 Update 
    service->updateDistance(distance);
}

