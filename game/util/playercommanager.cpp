#include "util/playercommanager.h"


PlayerComManager::PlayerComManager(QObject *parent) : QObject(parent){

}


void PlayerComManager::onTextMessageReceived(const QString &message) {
    qDebug() << "Receive message";
    qDebug() << message;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();



}
