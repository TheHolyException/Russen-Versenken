#include "russenversenken_server.h"

RussenVersenken_Server::RussenVersenken_Server()
{
    player1 = Player();
    player2 = Player();;
    phase =0;
}

void RussenVersenken_Server::sendGrid(Hexagon grid[10][10], Player *player) {
    std::map<std::string, JSONUtils::Value> gridMap;
    int pos = 0;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            Hexagon hex = grid[j][i];
            gridMap.insert({std::to_string(pos) , std::to_string(hex.isShipPart) + "#"+std::to_string(hex.isHit)});
            pos++;
        }
    }
    QString message = QString::fromStdString(JSONUtils::generateJSON(gridMap));
    player->sendPacket(151, message);
}

bool RussenVersenken_Server::AreAllShipsDown(Hexagon grid[10][10]){

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(grid[i][j].isShipPart && !grid[i][j].isHit){
                return false;
            }
        }
    }

    return true;
}
