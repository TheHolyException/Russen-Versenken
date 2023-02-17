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

void Player::sendPacket(int packetID, QString &message) {
    std::map<std::string, JSONUtils::Value> data {
        {"code", packetID},
        {"payload", message.toUtf8().toBase64().toStdString()}
    };
    webSocket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
}
