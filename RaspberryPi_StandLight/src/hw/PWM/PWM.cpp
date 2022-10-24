#include "PWM.h"

PWM::PWM(int pin, int min, int max)
    : pinNumber(pin), low(min), high(max)
{
    wiringPiSetup();
    softPwmCreate(pinNumber, low, high);
}

PWM::~PWM()
{

}


void PWM::Stopmotor()
{
   softPwmWrite(pinNumber, 0);
}

void PWM::startmotor(int speed)
{
    softPwmWrite(pinNumber, speed);
}

