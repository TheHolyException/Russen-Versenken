#include "websocketclient.h"

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent)
{
    m_webSocket = new QWebSocket();
    pmm = new PlayerComManager();

    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, pmm, &PlayerComManager::onTextMessageReceived);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocketClient::onError);
}

WebSocketClient::~WebSocketClient()
{
    m_webSocket->close();
    delete m_webSocket;
}

void WebSocketClient::connectToServer(const QUrl &url)
{
    m_webSocket->open(url);
}

void WebSocketClient::sendMessage(const QString &message)
{
    qDebug() << "Sending: " + message;
    m_webSocket->sendTextMessage(message);
}

void WebSocketClient::sendPacket(int packetID, QString &message) {
    std::map<std::string, JSONUtils::Value> data {
        {"code", packetID},
        {"UUID", pmm->getUUID().toStdString()},
        {"payload", message.toStdString()}
    };

    sendMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
}

void WebSocketClient::onConnected()
{
    emit connected();
}

void WebSocketClient::onDisconnected()
{
    emit disconnected();
}

void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "ERROR";
    //emit error(m_webSocket->errorString());
}
