#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H


#include <QWidget>
#include <QAbstractSocket>
#include <QWebSocket>

#include <chrono>
#include <thread>

#include "util/playercommanager.h"
#include "util/jsonutils.h"
#include "util/hexagon.h"


class WebSocketClient : public QObject
{
    Q_OBJECT

public:
    static WebSocketClient& getInstance()
    {
        static WebSocketClient instance;
        return instance;
    }
    void connectToServer(const QUrl &url);
    void sendMessage(const QString &message);
    void sendPacket(int packetId, const QString &payload);
    void waitUntilConnected();
    PlayerComManager getPlayerCommandManager();
    void sendGrid(Hexagon grid[10][10]);


signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void error(const QString &errorString);

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void onStatusChanged(QAbstractSocket::SocketState state);

private:
    WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();
    Q_DISABLE_COPY(WebSocketClient)

    QWebSocket *m_webSocket;
    PlayerComManager *pmm;
};

#endif // WEBSOCKETCLIENT_H
