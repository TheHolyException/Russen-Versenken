#ifndef SERVERCOMMANAGER_H
#define SERVERCOMMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "russenversenken_server.h"
#include "utils/hexagon.h"

class ServerComManager : public QObject
{
public:
    ServerComManager(QObject *parent = nullptr);


public slots:
    void onTextMessageReceived(const QString &message);
};

#endif // SERVERCOMMANAGER_H
