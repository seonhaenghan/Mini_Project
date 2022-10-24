#ifndef BUZZERSERVICE_H
#define BUZZERSERVICE_H
#include "Buzzer.h"

class BuzzerService
{
private:
    Buzzer *buzzer;
public:
    BuzzerService(Buzzer *buzzer);
    virtual ~BuzzerService();
    void buzzerSound(int state);
};

#endif