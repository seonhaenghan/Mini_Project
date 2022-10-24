#include "PWMService.h"

PWMService::PWMService(PWMView *pwmView)
{
    this->pwmView = pwmView;
}

PWMService::~PWMService()
{

}

void PWMService::updateState(std::string strState2)
{
    static int motor_power = POWER_LOW;
    // 바람의 세기
    if(strState2 == "windpowerButton")
    {
        motor_power++;
        motor_power %= 4;   
    }
    pwmView->powerState(motor_power);
}
// temp data 전송 
void PWMService::upDatetemp(DHT_Data dhtData)
{
    float temp;
    static int tempOver = 0;
    temp = dhtData.Temp + (float)(dhtData.TempDec/10.0);
    if(temp >= 23)
    {
        tempOver = 1;
    }
    else
    {
        tempOver = 0; 
    }
    pwmView->tempState(tempOver);
}