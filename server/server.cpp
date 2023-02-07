#include "server.h"
#include <QObject>
#include <QDateTime>

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


    QStringList tokens = QString( socket->readLine() ).split( "\r\n" );
    qDebug() << "Received" << tokens << tokens[0];
    if ( tokens[0] == "GET" )
    {
        qDebug() << "malaka";
        QTextStream os( socket );
        os.setAutoDetectUnicode( true );
        os << "HTTP/1.0 200 Ok\r\n"
        "Content-Type: text/html; charset=\"utf-8\"\r\n"
        "\r\n"
        "<h1>Hallo!</h1>\n"
        << QDateTime::currentDateTime().toString() << "\n";
        socket->close();

        if ( socket->state() == QTcpSocket::UnconnectedState )
        {
            delete socket;
        }
    }

}
