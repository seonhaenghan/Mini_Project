#include "DisplayView.h"

DisplayView::DisplayView(LCD *lcd)
{
    this->lcd = lcd;
}

DisplayView::~DisplayView()
{

}

void DisplayView::displayMode(int mode)
{
    char buffFront[30];
    char buffRear[30];
    char initbuff[30];
    switch(mode)
    {
        case CARD_READER:
            //LCD를 초기화 code test 진행해봐야 함 
            sprintf(initbuff, "                ");
            lcd->WriteStringXY(0, 0, initbuff);
            lcd->WriteStringXY(1, 0, initbuff);

            sprintf(buffRear, "MODE :");
            sprintf(buffFront, "CARD READER");
            lcd->WriteStringXY(0, 0, buffRear);
            lcd->WriteStringXY(1, 0, buffFront);
        break;

        case CARD_REGISTER:
            
            sprintf(initbuff, "                ");
            lcd->WriteStringXY(0, 0, initbuff);
            lcd->WriteStringXY(1, 0, initbuff);

            sprintf(buffRear, "MODE :");
            sprintf(buffFront, "CARD REGISTER");
            lcd->WriteStringXY(0, 0, buffRear);
            lcd->WriteStringXY(1, 0, buffFront);
        break;

        case CARD_DELETE:
            
            sprintf(initbuff, "                ");
            lcd->WriteStringXY(0, 0, initbuff);
            lcd->WriteStringXY(1, 0, initbuff);

            sprintf(buffRear, "MODE :");
            sprintf(buffFront, "CARD DELETE");
            lcd->WriteStringXY(0, 0, buffRear);
            lcd->WriteStringXY(1, 0, buffFront);
        break;

        case CARD_SEARCH:
            
            sprintf(initbuff, "                ");
            lcd->WriteStringXY(0, 0, initbuff);
            lcd->WriteStringXY(1, 0, initbuff);

            sprintf(buffRear, "MODE :");
            sprintf(buffFront, "CARD SEARCH");
            lcd->WriteStringXY(0, 0, buffRear);
            lcd->WriteStringXY(1, 0, buffFront);
    }
}