#include "onlineclient.h"

OnlineClient::OnlineClient(QObject *parent) : QObject (parent) {
    client = new QTcpSocket;
    connect(client, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(client, SIGNAL(readyRead()), this, SLOT(startRead));
}

OnlineClient::~OnlineClient() {
    client->close();
    client->deleteLater();
}

void OnlineClient::start(QString address, quint16 port) {
    QHostAddress addr (address);
    client->connectToHost(addr, port);
}

void OnlineClient::startTransfer() {
    QString str("ping");
    client->write(str.toLocal8Bit().data());
}

void OnlineClient::startRead() {
    char buffer[512] = {0};
    QTcpSocket *sender = (QTcpSocket*) QObject::sender();
    sender->read(buffer, sender->bytesAvailable());
    qDebug() << "Received: " << buffer;
}
