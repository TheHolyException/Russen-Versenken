#include "websocketclient.h"

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent)
{
    m_webSocket = new QWebSocket();
    pmm = new PlayerComManager();

    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_webSocket, &QWebSocket::stateChanged, this, &WebSocketClient::onStatusChanged);
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
    m_webSocket->sendTextMessage("Hello World!");
    m_webSocket->flush();
}

void WebSocketClient::sendMessage(const QString &message)
{
    qDebug() << "Sending: " + message;
    m_webSocket->sendTextMessage(message);
}

void WebSocketClient::sendPacket(int packetID, const QString &message) {
    std::map<std::string, JSONUtils::Value> data {
        {"code", packetID},
        {"UUID", pmm->getUUID().toStdString()},
        {"payload", message.toUtf8().toBase64().toStdString()}
    };

    sendMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
}

void WebSocketClient::waitUntilConnected() {
    while (!m_webSocket->isValid()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
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
    qDebug() << "ERROR " + m_webSocket->errorString();
}

void WebSocketClient::onStatusChanged(QAbstractSocket::SocketState state) {
    qDebug() << "Status Changed " + (int)state;
}

PlayerComManager WebSocketClient::getPlayerCommandManager() {
    return pmm;
}

void WebSocketClient::sendGrid(Hexagon grid[10][10]) {
    std::map<std::string, JSONUtils::Value> gridMap;
    int pos = 0;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            Hexagon hex = grid[i][j];

            std::map<std::string, JSONUtils::Value> data {
                {"s",   hex.isShipPart},
                {"h",   hex.isHit}
            };

            pos++;

            gridMap.insert({std::to_string(pos) , std::to_string(hex.isShipPart) + "#"+std::to_string(hex.isHit)});
        }
    }
    QString message = QString::fromStdString(JSONUtils::generateJSON(gridMap));
    sendPacket(151, message);
}
