#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QStringLiteral>

#include <QWebSocket>
#include <QWebSocketServer>

#include <QUuid>

#include "../utils/jsonutils.h"

/**
 * @class WebSocketServer
 * @brief A class for managing WebSocket connections.
 *
 * This class manages WebSocket connections using a QWebSocketServer and a
 * QList of QWebSocket objects. It provides methods for handling incoming
 * messages, establishing new connections, and broadcasting messages to all
 * connected clients.
 * @note
 * Code 200 - Connection established
 * Code 201 - Received Message
 * Code 202 - Received Binary Message
 * @example example_websocketserver_usage.cpp
 */
class WebSocketServer : public QObject
{
public:
    /**
     * @brief Constructs a WebSocketServer object with the given parent.
     * @param port The port number on which to listen for incoming connections.
     * @param parent The parent object.
     */
    WebSocketServer(quint16 port, QObject *parent = 0);

    // Add Docs
    ~WebSocketServer();

    /**
     * @brief Broadcasts a message to all connected clients.
     * @param message The message to broadcast.
     */
    static void broadcast(const QString &message);

    // Add Docs
    static WebSocketServer& getInstance(quint16 port = 8080);

private slots:
    /**
     * @brief Handles an incoming text message.
     * @param message The incoming text message.     */
    void onTextMessageReceived(QString message);

    /**
     * @brief Handles a new WebSocket connection.
     */
    void onNewConnection();

    /**
     * @brief Handles an incoming binary message.
     */
    void onBinaryMessageReceived(QByteArray message);

    /**
     * @brief Slot called when a socket is disconnected from the server
     * This method is called when a socket is disconnected from the server.
     * It removes the socket from the list of connected sockets, and deletes the socket object.
     */
    void onSocketDisconnected();

private:
    /**
     * @brief The main WebSocket server object
     * This member variable represents the main WebSocket server object.
     * It is used to listen for new connections, and to manage the list of connected sockets.
     */
    QWebSocketServer m_socketServer;

    /**
     * @brief List of connected sockets
     * This static member variable represents a list of all the sockets that are currently connected to the WebSocket server.
     * It can be accessed by any instance of the WebSocketServer class.
     */
    static QList<QWebSocket *> m_sockets;

    /**
     * @brief Pointer to the WebSocketServer singleton instance.
     * This is a static variable that holds the pointer to the WebSocketServer singleton instance.
     * It is used to ensure that only one instance of the WebSocketServer class is created throughout the program execution.
     * It is also used to access the singleton instance of the WebSocketServer class from other parts of the program.
     */
    static WebSocketServer* m_instance;

};

#endif // WEBSOCKETSERVER_H
