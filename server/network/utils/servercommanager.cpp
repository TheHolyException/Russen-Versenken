#include "servercommanager.h"

ServerComManager::ServerComManager(QObject *parent) : QObject(parent) {

}

void ServerComManager::onTextMessageReceived(const QString &message) {
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject data = document.object();

    switch (data["code"].toInt()) {



        default:
            qDebug() << "Unknown Packet -> " + message;
            break;
    }

}
