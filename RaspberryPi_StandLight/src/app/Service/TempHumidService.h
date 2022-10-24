#ifndef TEMPHUMIDSERVICE_H
#define TEMPHUMIDSERVICE_H

#include "DHT_Data.h"
#include "TempHumidView.h"
class TempHumidService
{
private:
    TempHumidView *tempHumidView;
public:
    TempHumidService(TempHumidView *tempHumidView);
    ~TempHumidService();
    void upDateEvent(DHT_Data dhtData);
};

#endif