#include <QCoreApplication>

#include "network/socket/websocketserver.h"
#include <thread>

void InitWebsocket(){
    WebSocketServer::getInstance(8888);
    qDebug() << "InitWebsocket";
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug("Hello World");

//    std::thread t1(InitWebsocket);
//    t1.detach();
    /*WebSocketServer &server = */WebSocketServer::getInstance(8888);

    //RussenVersenken_Server *RV_server = RussenVersenken_Server::getInstance();


    return a.exec();
}


