#include "DisplayService.h"

DisplayService::DisplayService(DisplayView *displayView)
{
    this->displayView = displayView; 
    modeState = 0; 
}

DisplayService::~DisplayService()
{

}

void DisplayService::updateStateEvent(std::string strstate)
{
    switch(modeState)
    {
        case CARD_READER:
        if(strstate == "ModeButton")
        {
            displayView->displayMode(CARD_REGISTER);
            modeState = CARD_REGISTER;
        }
        break;

        case CARD_REGISTER:
        if(strstate == "ModeButton")
        {
            displayView->displayMode(CARD_DELETE);
            modeState = CARD_DELETE;
        }
        break;

        case CARD_DELETE:
        if(strstate == "ModeButton")
        {
            displayView->displayMode(CARD_SEARCH);
            modeState = CARD_SEARCH;
        }
        break;

        case CARD_SEARCH:
        if(strstate == "ModeButton")
        {
            displayView->displayMode(CARD_READER);
            modeState = CARD_READER;
        }
        break;

        
    }
    
}


void DisplayService::updataStateMesg(int state)
{
    switch(state)
    {
        case CARD_READER:
            displayView->displayMode(CARD_READER);
        break;

        case CARD_REGISTER:  
            displayView->displayMode(CARD_REGISTER);
        break;

        case CARD_DELETE:   
            displayView->displayMode(CARD_DELETE);
        break;

        case CARD_SEARCH:
            displayView->displayMode(CARD_SEARCH);
        break;
    }
    
}