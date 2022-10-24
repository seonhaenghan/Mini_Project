#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include "View.h"
#include "LightState.h"
#include "DHT_Data.h"
// Service가 View에 의존한다. 
class Service
{
private:
    int lightState; 
    View *view;
    bool bDistanceLight; 
public:
    Service(View *viewer);
    virtual ~Service();
    void updateState(std::string strState);
    void upDateEvent(DHT_Data dhtData);
    void updateDistance(int distance);
};

#endif