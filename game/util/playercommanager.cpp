#include "util/playercommanager.h"

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
        break;

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
