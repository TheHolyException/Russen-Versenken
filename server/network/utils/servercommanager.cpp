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

    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }

}
