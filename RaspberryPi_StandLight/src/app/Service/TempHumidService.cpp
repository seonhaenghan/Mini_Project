#include "TempHumidService.h"

TempHumidService::TempHumidService(TempHumidView *tempHumidView)
{
    this->tempHumidView = tempHumidView;
}

TempHumidService::~TempHumidService()
{

}

void TempHumidService::upDateEvent(DHT_Data dhtData)
{
    float temp, humid;
    temp = dhtData.Temp + (float)(dhtData.TempDec/10.0);
    humid = dhtData.RH + (float)(dhtData.RHDec/10.0);
    tempHumidView->setTempHumidData(temp, humid);
}