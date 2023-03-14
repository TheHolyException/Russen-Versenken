#include <QCoreApplication>

#include "network/socket/websocketserver.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug("Hello World");
    /*WebSocketServer &server = */WebSocketServer::getInstance(8888);
    return a.exec();
}

