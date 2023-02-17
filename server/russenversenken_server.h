#ifndef RUSSENVERSENKEN_SERVER_H
#define RUSSENVERSENKEN_SERVER_H

#include "utils/player.h"
#include <QObject>

class RussenVersenken_Server
{
public:

    static RussenVersenken_Server& getInstance()
    {

        if (!m_instance) {
           m_instance = new RussenVersenken_Server();
        }
        return *m_instance;
    }
    Player player1;
    Player player2;
    int phase;

    void sendGrid(Hexagon grid[10][10], Player *player);
private:
    RussenVersenken_Server();
    inline static RussenVersenken_Server *m_instance;

};

#endif // RUSSENVERSENKEN_SERVER_H
