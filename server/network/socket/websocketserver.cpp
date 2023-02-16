#include "websocketserver.h"

QList<QWebSocket *> WebSocketServer::m_sockets;

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    if (!m_socketServer.listen(QHostAddress::Any, port)) {
        qFatal("Failed to open web socket server.");
    }

    m_instance = this;
    scm = new ServerComManager();

    qDebug() << "WebSocket server listening on port" << m_socketServer.serverPort();
    connect(&m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

WebSocketServer::~WebSocketServer() {
    m_socketServer.close();
    qDeleteAll(m_sockets.begin(), m_sockets.end());
}

WebSocketServer* WebSocketServer::m_instance = nullptr;

WebSocketServer& WebSocketServer::getInstance(quint16 port)
{
    if(!m_instance)
        m_instance = new WebSocketServer(port);
    return *m_instance;
}

void WebSocketServer::onNewConnection() {
    qDebug() << "New user";
    QWebSocket *socket = m_socketServer.nextPendingConnection();

    // Give every Connection an ID and send that ID to Player
    // Player will save that ID, it will act as an authentication Token
    QString playerId = QUuid::createUuid().toString();

    RussenVersenken_Server &rserver=RussenVersenken_Server::getInstance();

    if( rserver.player1.uuid==""){
        rserver.player1.uuid=playerId;
    }else{
        rserver.player2.uuid=playerId;
    }

    std::map<std::string, JSONUtils::Value> joinConfirmation {
        {"code", 200},
        {"UUID", playerId.toStdString()}
    };
    socket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(joinConfirmation)));

    std::map<std::string, JSONUtils::Value> data {
        {"code", 201},
        {"UUID", playerId.toStdString()}
    };
    broadcast(QString::fromStdString(JSONUtils::generateJSON(data)));

    // Connect to the socket's signals
    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
    m_sockets.append(socket);

    /*
     * Test Setup
     *
     */

    std::map<std::string, JSONUtils::Value> initPacket {
        {"code", 101},
        {"opponent", "RandomDude"}
    };
    broadcast(QString::fromStdString(JSONUtils::generateJSON(initPacket)));


}

void WebSocketServer::onTextMessageReceived(QString message) {
    qDebug() << "Received message " << message;
    scm->onTextMessageReceived(message);
    // This method has been deprecated.
}

void WebSocketServer::onBinaryMessageReceived(QByteArray message) {
    qDebug() << "Received binary message of size" << message.size() << "bytes";

    // Send a response back to the client
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    if (senderSocket) {
        std::map<std::string, JSONUtils::Value> data{
          {"code", 202},
          {"message", "Received Binary Message!"},
          {"received_message", message.toStdString()}
        };
        senderSocket->sendBinaryMessage(QString::fromStdString(JSONUtils::generateJSON(data)).toUtf8());
    }
}

void WebSocketServer::onSocketDisconnected() {
    // Get the disconnected socket
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Disconnected one User.";

    // Remove the socket from the list of connected sockets
    m_sockets.removeOne(socket);

    // Notify Players
    std::map<std::string, JSONUtils::Value> data{
        {"code", 203},
        {"message", "One Player disconnected!"}
    };
    for (QWebSocket *socket : m_sockets) {
        socket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
    }

    // Disconnected all Users

    for (QWebSocket *socket : m_sockets) {
        socket->disconnect();
    }

    RussenVersenken_Server rserver=RussenVersenken_Server::getInstance();

    rserver.player1.uuid="";
    rserver.player2.uuid="";

    m_sockets.clear();

    // Delete the socket
    socket->deleteLater();
}

void WebSocketServer::broadcast(const QString &message) {
    // Iterate over the list of connected sockets
    for (auto socket : m_sockets) {
        // Send the message to the socket
        socket->sendTextMessage(message);
    }
}
