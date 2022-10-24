#include "Buzzer.h"

Buzzer::Buzzer(int pin, int min, int max)
: pinNumber(pin), low(min), high(max)
{
    wiringPiSetup();
    softPwmCreate(pinNumber, low, high);
}

Buzzer::~Buzzer()
{

}

void Buzzer::stopBuzzer()
{
   softPwmWrite(pinNumber, 0);
}

void Buzzer::startBuzzer(int value)
{
    softPwmWrite(pinNumber, value);
}