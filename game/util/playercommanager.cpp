#include "util/playercommanager.h"
#include "russenversenken.h"
#include "websocketclient.h"

PlayerComManager::PlayerComManager(QObject *parent) : QObject(parent){

}

void PlayerComManager::setUUID(QString &message) {
     this->uuid = message;
}

QString PlayerComManager::getUUID() {
    return this->uuid;
}

void PlayerComManager::onTextMessageReceived(const QString &message) {
    qDebug() << "received from server " + message;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject data = jsonDoc.object();

    RussenVersenken &r = RussenVersenken::getInstance();

    switch (data["code"].toInt()) {
    case 101: // Init game Lobby
        this->onInit(data);
        break;
    case 111: // Init game

        break;
    case 200: // Response to self Joined
        this->uuid = data["UUID"].toString();
        break;

    case 201: // Player Joined
        qDebug() << "New player joined: " + data["UUID"].toString();
        r.addChatmessage("Neuer Spieler beigetreten!\n");
        break;
    case 602: {// Chat message received

        QString m =QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded;
        r.addChatmessage(m + "\n");

        break;
    }
    case 801: // Game Tick
        qDebug() << "GameTick";
        break;

    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }
}


void PlayerComManager::onInit(QJsonObject &data) {
    qDebug() << data;
}
