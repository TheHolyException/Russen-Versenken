#ifndef PLAYERCOMMANAGER_H
#define PLAYERCOMMANAGER_H



#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

class view_waitingInQueue;

class PlayerComManager : public QObject
{
    Q_OBJECT


public:
    PlayerComManager(QObject *parent = nullptr);
    void setUUID(QString &uuid);
    QString getUUID();
    void onInit(QJsonObject &message);

private:
    QString uuid;

public slots:
    void onTextMessageReceived(const QString &message);

};

#endif // PLAYERCOMMANAGER_H
