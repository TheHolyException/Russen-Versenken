#ifndef RUSSENVERSENKEN_SERVER_H
#define RUSSENVERSENKEN_SERVER_H

#include "util/player.h"
#include <QObject>

class RussenVersenken_Server
{
public:
    RussenVersenken_Server();

private:
    Player player1;
    Player player2;
    int phase;
};

#endif // RUSSENVERSENKEN_SERVER_H
