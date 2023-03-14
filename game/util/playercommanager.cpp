#include "util/playercommanager.h"
#include "russenversenken.h"
#include "ui_russenversenken.h"
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

    RussenVersenken *r = RussenVersenken::getInstance();

    QJsonDocument payloadDoc = QJsonDocument::fromJson(QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded);
    QJsonObject payloadData = payloadDoc.object();

    QString m;

    switch (data["code"].toInt()) {
    case 101: // Init game Lobby
        this->onInit(data);
        break;
    case 111: // Init game

        break;
    case 151: {// Receive Grid Data
        qDebug() << payloadData;

        for (int i = 0; i < 100; i ++) {
            QStringList datas = payloadData[QString::fromStdString(std::to_string(i))].toString().split("#");
            r->grid[i%10][i/10].isShipPart = datas.at(0) == "0" ? false : true;
            r->grid[i%10][i/10].isHit      = datas.at(1) == "0" ? false : true;
        }
        r->update();

        break;
    }
    case 200: // Response to self Joined
        this->uuid = data["UUID"].toString();
        break;

    case 201: // Player Joined
        qDebug() << "New player joined: " + data["UUID"].toString();
        r->addChatmessage("Neuer Spieler beigetreten!\n");
        break;
    case 301: {// phase change

        m =QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded;
        int mPhase= m.toInt();
        r->phase = mPhase;
        if(mPhase==1){
            r->isPlayersTurn=true;
        }else if(mPhase==2){
            qDebug()<< "phase zwei begonnen";
        }

        break;
    }
    case 602: {// Chat message received

        m =QByteArray::fromBase64Encoding(data["payload"].toString().toUtf8()).decoded;
        r->addChatmessage(m + "\n");
        r->ui->chat->verticalScrollBar()->setValue(r->ui->chat->verticalScrollBar()->maximum());

        break;
    }
    case 801: // Is Players Turn
        qDebug() << "Is Players Turn";
        r->isPlayersTurn=true;
        m="Du bist an der Reihe!";
        r->addChatmessage(m + "\n");
        break;

    default:
        qDebug() << "Unknown Packet -> " + message;
        break;
    }
}


void PlayerComManager::onInit(QJsonObject &data) {
    qDebug() << data;
}
