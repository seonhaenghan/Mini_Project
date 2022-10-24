#include "BuzzerService.h"

BuzzerService::BuzzerService(Buzzer *buzzer)
{
    this->buzzer = buzzer;
}

BuzzerService::~BuzzerService()
{

}

void BuzzerService::buzzerSound(int state)
{
    if(state)
    {
        buzzer->startBuzzer(90);
    }
    else
    {
        buzzer->stopBuzzer();
    }
    
}