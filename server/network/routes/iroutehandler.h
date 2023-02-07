#ifndef IROUTEHANDLER_H
#define IROUTEHANDLER_H

#include <QTcpSocket>
#include <QString>

/**
 * @class IRouteHandler
 * @brief An interface for handling HTTP route requests.
 * This interface defines a method for handling HTTP route requests.
 * It is intended to be used in conjunction with the HttpServer class, which allows users to register route handlers for specific paths and HTTP methods.
 * @fn void IRouteHandler::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
 * @brief Handles an HTTP route request.
 * @param socket The socket representing the connection to the client.
 * @param parameters A map of parameters passed with the request.
 * This method should be implemented by subclasses to handle the logic for a specific route.
 * The socket can be used to send a response to the client, and the parameters map contains any query parameters or form data passed with the request.
 */
class IRouteHandler
{
public:
    virtual void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) = 0;
};

#endif // IROUTEHANDLER_H
