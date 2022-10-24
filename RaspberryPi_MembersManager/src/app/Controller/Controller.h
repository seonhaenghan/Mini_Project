#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Monitor.h"
#include "DeviceData.h"
#include "MembersManageService.h"
#include "DisplayService.h"
#include "State.h"
#include "BuzzerService.h"
class Controller
{
private:
   //Monitor *monitor;
    MembersManageService *membersManageService;
    DisplayService *displayService;
    BuzzerService *buzzerService;
public:
    Controller(MembersManageService *membersManageService, DisplayService *displayService, BuzzerService *buzzerService);
    virtual ~Controller();
    void updateEvent(DeviceData data);
    void updataClientmesg(char *buff);
    void cardCheck(int state);
};

#endif /* __CONTROLLER_H__ */
