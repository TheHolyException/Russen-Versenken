#include <QCoreApplication>

#include "network/socket/websocketserver.h"
#include "csvinterface.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug("Hello World");
    /*WebSocketServer &server = */WebSocketServer::getInstance(8888);
    CSVInterface::init();
    CSVInterface::debug();
    CSVInterface::afterMatch(0, 1, 1, 3);

    return a.exec();
}

