#ifndef ONLINECLIENT_H
#define ONLINECLIENT_H

#include <QObject>

#include <QString>
#include <QTcpSocket>
#include <QHostAddress>

class OnlineClient : public QObject {
    Q_OBJECT
private:
    QTcpSocket *client;
public:
    OnlineClient(QObject *parent = 0);
    ~OnlineClient();
    void start(QString address, quint16 port);
public slots:
    void startTransfer();
    void startRead();
};

#endif // ONLINECLIENT_H
