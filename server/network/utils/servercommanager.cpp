#include "servercommanager.h"

ServerComManager::ServerComManager(QObject *parent) : QObject(parent) {

}

void ServerComManager::onTextMessageReceived(const QString &message) {
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject data = document.object();

    QString uuid = data["UUID"].toString();
    qDebug() << data["code"].toInt();

    QJsonDocument payloadDoc = QJsonDocument::fromJson(QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded);
    QJsonObject payloadData = payloadDoc.object();

    RussenVersenken_Server &rServer =RussenVersenken_Server::getInstance();

    switch (data["code"].toInt()) {

    case 151: {// Receive Grid Data
        qDebug() << payloadData;
        Hexagon grid[10][10];

        for (int i = 0; i < 100; i ++) {
            qDebug() << payloadData[QString::fromStdString(std::to_string(i))].toString();
            Hexagon hex;
            QStringList datas = payloadData[QString::fromStdString(std::to_string(i))].toString().split("#");
            hex.isShipPart = datas.at(0) == "0" ? false : true;
            hex.isHit      = datas.at(1) == "0" ? false : true;
        }

        break;       
    }
    case 501: {// Receive Player Name
        qDebug() << payloadData;

        QString m="1";
        if(uuid == rServer.player1.uuid){
            rServer.player1.name=payloadData["name"].toString();
            rServer.player1.sendPacket(301,m);
        }else if(uuid == rServer.player2.uuid){
            rServer.player2.name=payloadData["name"].toString();
            rServer.player2.sendPacket(301,m);
        }
        //qDebug() << rServer.player1.name;
        break;
    }
    case 601: {// Receive Chatmessage
        qDebug() << payloadData;


        if(uuid == rServer.player1.uuid){
            QString m = rServer.player1.name +": "+payloadData["ChatNachricht"].toString();
            rServer.player2.sendPacket(602,m);
        }else if(uuid == rServer.player2.uuid){
            QString m = rServer.player2.name +": "+payloadData["ChatNachricht"].toString();
            rServer.player1.sendPacket(602,m);
        }
        //qDebug() << rServer.player1.name;
        break;
    }
    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }

}
