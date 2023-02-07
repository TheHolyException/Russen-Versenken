#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QString>

#include <string>
#include "../utils/ws_utils.h"
#include "../routes/iroutehandler.h"

/**
 * @class HttpServer
 * @brief A TCP server that handles HTTP requests
 * This class is a subclass of QTcpServer and handles incoming HTTP requests.
 * It listens for incoming connections on a specified port and invokes a callback function
 * for each request based on the path and method specified in the request.
 * @note This class does not handle multiple requests concurrently. 
 * It processes one request at a time.
 */
class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    /**
     * @brief Constructs an HttpServer object with the given parent.
     * @example example_http_usage.cpp
     * @param parent The QObject parent.
     */
    HttpServer(QObject *parent = 0);

    /**
     * @brief Destroys the HttpServer object.
     */
    ~HttpServer();

    /**
     * @brief Starts listening for incoming connections on the specified port.
     * @param port The port number to listen on.
     * @return true if the server was successfully started, false otherwise.
     */
    bool start(quint16 port);

    /**
     * @brief Returns a human-readable description of the last error that occurred.
     * @return A QString containing the error description.
     */
    QString errorString() const;

    /**
     * @brief Adds a route to the server.
     * @param path The path of the route to add.
     * @param method The HTTP method to handle for the route.
     * @param handler The IRouteHandler object that will handle the route.
     * This method adds a route to the server and associates it with the given
     * IRouteHandler object. When a request is received by the server with the
     * specified path and method, the handleRoute method of the handler object
     * will be called.
     */
    void addRoute(const QString &path, const QString &method, IRouteHandler *handler);

protected:

    /**
     * @brief Handles an incoming connection request.
     * @param socketDescriptor The descriptor for the incoming connection.
     * @note This method is called by the operating system when a new connection is requested.
     */
    void incomingConnection(qintptr socketDescriptor);

private:
    /**
     * @class Route
     * @brief A struct representing a route in the HTTP server. A route consists of an HTTP method (e.g. GET, POST) and a callback function that is called when a request matching the method and path of the route is received.
     * @var Route::method The HTTP method for the route.
     * @var Route::callback The callback function for the route. It takes in a pointer to a QTcpSocket representing the client and a QMap containing the request parameters as arguments.
     */
    struct Route
    {
        QString method;
        std::function<void(QTcpSocket *, const QMap<QString, QString> &)> callback;
    };

    /**
    * @var QMap<QString, Route> m_routes
    * @brief A map of routes in the HTTP server, indexed by the path of the route.
    */
    QMap<QString, Route> m_routes;
};

#endif // WEBSERVER_H
