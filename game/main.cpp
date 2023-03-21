#include "russenversenken.h"

#include <QApplication>

// STD Imports
#include <iostream> // std::cout

// Custom Modules
#include "websocketclient.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RussenVersenken *ඞ= RussenVersenken::getInstance();
        ඞ->show();

    WebSocketClient &client = WebSocketClient::getInstance();
    client.connectToServer(QUrl("ws://localhost:8888"));
    client.sendMessage("Malaka");

    return a.exec();
}
