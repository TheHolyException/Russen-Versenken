#include "servercommanager.h"

ServerComManager::ServerComManager(QObject *parent) : QObject(parent) {

}

void ServerComManager::onTextMessageReceived(const QString &message) {
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject data = document.object();

    RussenVersenken_Server *rServer =RussenVersenken_Server::getInstance();

    QString uuid = data["UUID"].toString();
  //  qDebug() << data["code"].toInt();
    Player *player=nullptr;
    if(uuid == rServer->player1.uuid){
        player = &rServer->player1;

    }else if(uuid == rServer->player2.uuid){
        player = &rServer->player2;
    }

    QJsonDocument payloadDoc = QJsonDocument::fromJson(QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded);
    QJsonObject payloadData = payloadDoc.object();

    QString m ="";

    switch (data["code"].toInt()) {

    case 151: {// Receive Grid Data
       // qDebug() << payloadData;
        Hexagon grid[10][10];

        for (int i = 0; i < 100; i ++) {
            Hexagon hex;
            QStringList datas = payloadData[QString::fromStdString(std::to_string(i))].toString().split("#");
            hex.isShipPart = datas.at(0) == "0" ? false : true;
            hex.isHit      = datas.at(1) == "0" ? false : true;
            player->grid[i%10][i/10] = hex;
        }
        player->isReady=true;

        break;       
    }
    case 152: {// Receive Hit Data
        qDebug() << payloadData;



        int x=payloadData["x"].toString().toInt();
        int y=payloadData["y"].toString().toInt();

        rServer->hit.setX(x);
        rServer->hit.setY(y);
        player->isReady=true;
        if(uuid == rServer->player1.uuid){
            rServer->player2.grid[x][y].isHit=true;
        }else if(uuid == rServer->player2.uuid){
             rServer->player1.grid[x][y].isHit=true;
        }

        break;
    }
    case 153: {// Receive Ready
        qDebug() << payloadData;

        player->isReady=true;

        break;
    }
    case 501: {// Receive Player Name
        qDebug() << payloadData;

        m="1";
        if(uuid == rServer->player1.uuid){
            rServer->player1.name=payloadData["name"].toString();
            rServer->player1.sendPacket(301,m);
        }else if(uuid == rServer->player2.uuid){
            rServer->player2.name=payloadData["name"].toString();
            rServer->player2.sendPacket(301,m);
        }

        m = "Bitte setze deine Schiffe und Bestätige ihre Position mit dem \"Bereit\"-Knopf.";
        player->sendPacket(602,m);
        //qDebug() << rServer.player1.name;
        break;
    }
    case 601: {// Receive Chatmessage
        qDebug() << payloadData;


        if(uuid == rServer->player1.uuid && rServer->player2.uuid!=""){
            m = rServer->player1.name +": "+payloadData["ChatNachricht"].toString();
            rServer->player2.sendPacket(602,m);
        }else if(uuid == rServer->player2.uuid && rServer->player1.uuid!=""){
            m = rServer->player2.name +": "+payloadData["ChatNachricht"].toString();
            rServer->player1.sendPacket(602,m);
        }
        //qDebug() << rServer.player1.name;
        break;
    }
    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }

}
