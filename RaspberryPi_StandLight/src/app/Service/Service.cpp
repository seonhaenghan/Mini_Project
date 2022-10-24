#include "Service.h"

Service::Service(View *viewer)
{
    view = viewer;
    // View의 주소를 넘겨 상태를 전달한다. 
    lightState = LIGHT_OFF; 
    // LED가 꺼진 상태
    // 생성자에서 initial 
    bDistanceLight = false; 
}

Service::~Service()
{

}



void Service::upDateEvent(DHT_Data dhtData)
{
    float temp;
    temp = dhtData.Temp + (float)(dhtData.TempDec/10.0);
    if(temp >= 28)
    {
        view->setState(LIGHT_OFF);
    }
}


void Service::updateState(std::string strState)
{
    switch (lightState)
    {
        case LIGHT_OFF:
            if (strState == "modeButton") {
                lightState = LIGHT_1;
            }
            
            view->setState(lightState);
        break;

        case LIGHT_1:
            if (strState == "modeButton") {
                lightState = LIGHT_2;
            }

            if (strState == "powerButton") {
                lightState = LIGHT_OFF;
            }

            if(bDistanceLight)    //거리가 범위 내에 있는 경우 
            {
                view->setState(lightState);
            }
            else
            {
                view->setState(LIGHT_OFF);
            }
        break;
        
        case LIGHT_2:
            if (strState == "modeButton") {
                lightState = LIGHT_3;
            }

            if (strState == "powerButton") {
                lightState = LIGHT_OFF;
            }

            if(bDistanceLight)    //거리가 범위 내에 있는 경우 
            {
                view->setState(lightState);
            }
            else
            {
                view->setState(LIGHT_OFF);
            }
        break;

        case LIGHT_3:
            if (strState == "modeButton") {
                lightState = LIGHT_4;
            }

            if (strState == "powerButton") {
                lightState = LIGHT_OFF;
            }

            if(bDistanceLight)    //거리가 범위 내에 있는 경우 
            {
                view->setState(lightState);
            }
            else
            {
                view->setState(LIGHT_OFF);
            }
        break;

        case LIGHT_4:
            if (strState == "modeButton") {
                lightState = LIGHT_5;
            }

            if (strState == "powerButton") {
                lightState = LIGHT_OFF;
            }

            if(bDistanceLight)    //거리가 범위 내에 있는 경우 
            {
                view->setState(lightState);
            }
            else
            {
                view->setState(LIGHT_OFF);
            }
        break;

        case LIGHT_5:
            if (strState == "modeButton") {
                lightState = LIGHT_OFF;
            }

            if (strState == "powerButton") {
                lightState = LIGHT_OFF;
            }

            if(bDistanceLight)    //거리가 범위 내에 있는 경우 
            {
                view->setState(lightState);
            }
            else
            {
                view->setState(LIGHT_OFF);
            }
        break;

    }
}
// Service:: (Service라는 Class의 소속임)

void Service::updateDistance(int distance)
{
    static int FalseCount = 0;
    //printf("distance : %d, %d\n", distance, FalseCount);
    if(distance < 0)    // 범위 내에 물체가 없다면  Light off
    {
        bDistanceLight = false;
        FalseCount++;
        if(FalseCount > 9)
        {
            FalseCount = 0;
            view->setState(LIGHT_OFF);
        } 
    }
    else                // 범위 내에 물체가 있는 경우 Light on
    {
        FalseCount = 0;
        bDistanceLight = true;
        view->setState(lightState);
    }
}