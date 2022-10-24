#include "Controller.h"
#include <iostream>

Controller::Controller(MembersManageService *membersManageService, DisplayService *displayService,
BuzzerService *buzzerService)
{
    //monitor = new Monitor();
    //membersManageService = new MembersManageService();
    this->displayService = displayService; 
    this->membersManageService = membersManageService;
    this->buzzerService = buzzerService;
}

Controller::~Controller()
{
}

void Controller::updateEvent(DeviceData data)
{
    if(data.devName == "cardReader")
    {
        int cardNumber[5];
        for(int i = 0; i < 5; i++)
            cardNumber[i] = data.devData[i];

        membersManageService->checkCardNumber(cardNumber);
       
    }
    if(data.devName == "ModeButton")
    {
        membersManageService->updateStateEvent(data.devName);
        displayService->updateStateEvent("ModeButton");
    }

}

void Controller::updataClientmesg(char *buff)
{
    membersManageService->buffData(buff);
    
    const char *comBuffReader = "READER";
    const char* comBuffRegister = "REGISTER";
    const char* comBuffDelete = "DELETE";
    const char* comBuffSerach = "SEARCH";
    /**/
    /*test code*/
    //int temp;
    // temp = strncmp(buff, comBuffReader, 5);
    // printf("tmep :::::: %d\n",temp);
    if(strncmp(buff, comBuffReader, 5) == 0)
    {
        
        membersManageService->updateStateMesg(CARD_READER);
        displayService->updataStateMesg(CARD_READER);
    } 
    if(strncmp(buff, comBuffRegister, 5) == 0)
    {
        membersManageService->updateStateMesg(CARD_REGISTER);
        displayService->updataStateMesg(CARD_REGISTER);
    }
    if(strncmp(buff, comBuffDelete, 5) == 0)
    {
        printf("CARD_DELETE_MODE\n");
       membersManageService->updateStateMesg(CARD_DELETE);
       displayService->updataStateMesg(CARD_DELETE);
    }
    if(strncmp(buff, comBuffSerach, strlen(comBuffSerach)) == 0)
    {
        printf("CARD_SEARCH_MODE\n");
        membersManageService->updateStateMesg(CARD_SEARCH);
        displayService->updataStateMesg(CARD_SEARCH);
    }
}

void Controller::cardCheck(int state)
{
    if(state)
    {
        buzzerService->buzzerSound(state);
    }
    else
    {
        buzzerService->buzzerSound(state);
    }
    
}
