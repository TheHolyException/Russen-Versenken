#ifndef PLAYER_H
#define PLAYER_H

#include "utils/hexagon.h"
#include <QObject>

class Player
{
public:
    Player();

    QString name;
    QString uuid;
    Hexagon grid[10][10];
};

#endif // PLAYER_H
