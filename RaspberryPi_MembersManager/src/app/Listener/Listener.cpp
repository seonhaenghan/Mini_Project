#include "Listener.h"
#include <string.h>

Listener::Listener(Controller *controller)
{
    rfid = new CardReader(new SPI(10, 3000000));
    modeButton = new ManageButton(27, "ModeButton");
    //controller = new Controller();
    this->controller = controller;
}

Listener::~Listener()
{
}

void Listener::checkEvent()
{
    if (checkRfid()) {  // 읽은 카드 정보를 controller로 전송 
        controller->updateEvent(rfid->getCardNumber());
    }

    if (modeButton->checkButton()) {    // 버튼 정보를 전송 
        controller->updateEvent(modeButton->getButtonData());
    }

    //controller->updataState();
    

}

bool Listener::checkRfid()
{// 1초 마다 카드 정보를 읽음 
    static unsigned int prevCheckTime = 0;
    
    if (millis() - prevCheckTime < 300) {
        return false;
    }
    prevCheckTime = millis();
    
    
    if (rfid->isCard()) 
    {
        controller->cardCheck(1);
        return true;
    }
    else{
        controller->cardCheck(0);
        return false;
    } 
}