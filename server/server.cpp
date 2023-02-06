#include "server.h"
#include <QObject>

Server::Server(QObject *parent) : QObject(parent) {
    server = new QTcpServer;

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server->listen(QHostAddress::Any, 8888);
}

Server::~Server() {
    server->close();
    //if (client != NULL) client->close();
    server->deleteLater();
}

void Server::acceptConnection() {
   QTcpSocket *client = server->nextPendingConnection();

   // TODO: Multiple user support


   connect (   client,
               SIGNAL(readyRead()),
               this,
               SLOT(startRead())
               );

}

void Server::startRead() {
    QTcpSocket *socket = (QTcpSocket*) QObject::sender();

    if (!socket->canReadLine()) return;

    QStringList tokens = QString(socket->readLine()).split("\r\n");
    qDebug() << tokens[0];
    socket->write("Hello World from Server");

}
