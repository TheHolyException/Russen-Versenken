#ifndef RUSSENVERSENKEN_SERVER_H
#define RUSSENVERSENKEN_SERVER_H

#include "qpoint.h"
#include "utils/player.h"
#include <QObject>

class RussenVersenken_Server : public QObject
{
    Q_OBJECT
public:

    static RussenVersenken_Server *getInstance()
    {

        if (!m_instance) {
           m_instance = new RussenVersenken_Server();
        }
        return m_instance;
    }
    Player player1;
    Player player2;
    int phase;
    Player *activePlayer=nullptr;
    QPoint hit;
    bool waitingForOtherPlayer;



    void sendGrid(Hexagon grid[10][10], Player *player);
    bool AreAllShipsDown(Hexagon grid[10][10]);
    void Game();
    void gameWon(Player *player);
private:
    RussenVersenken_Server();
    inline static RussenVersenken_Server *m_instance;

};

#endif // RUSSENVERSENKEN_SERVER_H
