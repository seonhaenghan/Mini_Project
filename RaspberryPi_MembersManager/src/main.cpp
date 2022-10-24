#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>
#include "GolfMembershipManager.h"
#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "MembersEntity.h"
#include "tcpServer.h"
#include "ComDev.h"
#include "DisplayService.h"
#include "DisplayView.h"
#include <cstring>
#include <softPwm.h>
#include "Buzzer.h"
#include "BuzzerService.h"

void serverThread(tcpServer *server, Controller *control)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            control->updataClientmesg(recvBuff);
            recvBuff[recvLen] = '\0';
           // server->sendData(recvBuff, recvLen);
            //sprintf(clientInputData ,"%s", recvBuff); 
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    LCD lcd(new I2C("/dev/i2c-1",0x27));
    Buzzer buzzer(26, 0, 100);
    BuzzerService *buzzerService = new BuzzerService(&buzzer);
    tcpServer *cardTcpServer = new tcpServer(5100);
    ComDev *comDev = new ComDev(cardTcpServer);
    MembersManageService *membersManageSerivce = new MembersManageService(comDev);
    DisplayView *displayView = new DisplayView(&lcd);
    DisplayService *displayService = new DisplayService(displayView);
    Controller *controller = new Controller(membersManageSerivce ,displayService, buzzerService);
    Listener *listener = new Listener(controller);
    std::thread threadFunc(serverThread, cardTcpServer, controller);

    //GolfMembershipManager golfMembershipManager;

    //golfMembershipManager.run();
    while(1)
    {
        listener->checkEvent();
        delay(50);
    }
    
    return 0;
}
