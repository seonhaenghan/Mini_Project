#ifndef PWMSERVICE_H
#define PWMSERVICE_H
#include "PWMView.h"
#include <string>
#include "DHT_Data.h"
#include "MotorPowerState.h"
// 문자열 사용 시 필요 

class PWMService
{
private:
    PWMView *pwmView;

public:
    PWMService(PWMView *pwmView);
    virtual ~PWMService();
    void updateState(std::string strState2);
    void upDatetemp(DHT_Data dhtData);
};

#endif