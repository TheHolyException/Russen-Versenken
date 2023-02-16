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

    switch (data["code"].toInt()) {

    case 151: {// Receive Grid Data
        qDebug() << payloadData;
        Hexagon grid[10][10];

        for (int i = 0; i < 100; i ++) {
            Hexagon hex;
            qDebug() << payloadData[QString::fromStdString(std::to_string(i))];
        }

        break;       
    }
    case 501: {// Receive Player Name
        qDebug() << payloadData;

        RussenVersenken_Server &rserver =RussenVersenken_Server::getInstance();

        if(uuid == rserver.player1.uuid){
            rserver.player1.name=payloadData["name"].toString();
        }else{
            rserver.player2.name=payloadData["name"].toString();
        }
        qDebug() << rserver.player1.name;
        RussenVersenken_Server &rserver2 =RussenVersenken_Server::getInstance();
          qDebug() << rserver2.player1.name;
        break;
    }
    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }

}
