#include "player.h"

Player::Player()
{
    uuid="";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j]= Hexagon(i+1,j+1);
        }
    }
}
