#include "websocketserver.h"

int main()
{
    // Create a WebSocket server on port 8000
    quint16 port = 8000;
    WebSocketServer server(port);

    // Connect to the server's newConnection signal
    QObject::connect(&server, &WebSocketServer::newConnection, []()
    { 
        qDebug() << "New connection established!"; 
    });

    // Connect to the server's textMessageReceived signal
    QObject::connect(&server, &WebSocketServer::textMessageReceived, [](const QString &message)
    { 
        qDebug() << "Received message:" << message; 
    });

    // Broadcast a message to all connected clients
    WebSocketServer::broadcast("Hello from the server!");
}
