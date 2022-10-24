#include "PWMView.h"

PWMView::PWMView(PWM *pwm)
{
    this->pwm = pwm;
    powermode = POWER_OFF;
    tempsign = 0;
}

PWMView::~PWMView()
{

}

void PWMView::powerState(int motor_power)
{
    powermode = motor_power;
}

void PWMView::tempState(int tempOver)
{
    if(tempOver)
    {
         switch (powermode)
        {
        case POWER_LOW:
        pwm->startmotor(60);
            break;

        case POWER_MID:
        pwm->startmotor(70);
            break;

        case POWER_HIGH:
        pwm->startmotor(99);
            break;

        case POWER_OFF:
        pwm->Stopmotor();
            break;
        }
    }
    else
    {
        pwm->Stopmotor();
    }
   
}



