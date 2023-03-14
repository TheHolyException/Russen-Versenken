#ifndef PLAYER_H
#define PLAYER_H

#include "qwebsocket.h"
#include "utils/hexagon.h"
#include <QObject>
#include "network/utils/jsonutils.h"

class Player
{
public:
    Player();

    QString name;
    QString uuid;
    Hexagon grid[10][10];
    QWebSocket *webSocket;

    bool isReady;

    void sendPacket(int packet, QString &message);
};

#endif // PLAYER_H
