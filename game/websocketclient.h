#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H


#include <QWidget>
#include <QAbstractSocket>
#include <QWebSocket>

#include "util/playercommanager.h"

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

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void error(const QString &errorString);

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);

private:
    WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();
    Q_DISABLE_COPY(WebSocketClient)

    QWebSocket *m_webSocket;
    PlayerComManager *pmm;
};

#endif // WEBSOCKETCLIENT_H
