#ifndef DISPLAYSERVICE_H
#define DISPLAYSERVICE_H
#include <string>
#include "State.h"
#include "DisplayView.h"
#include "MembersManageService.h"
class DisplayService
{
private:
    DisplayView *displayView;
    
    int modeState;
public:
    DisplayService(DisplayView *displayView);
    virtual ~DisplayService();
    void updateStateEvent(std::string strstate);
    void updataStateMesg(int state);
};

#endif