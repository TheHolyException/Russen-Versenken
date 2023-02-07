#include "httptestroute.h"

HTTPTestRoute::HTTPTestRoute() { }

void HTTPTestRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    std::string response = WSUtils::createHTMLResponse("<h1>Working!!</h1>");
    // Consider implementing something that would directly read the content of a file


    socket->write(response.c_str());
    socket->close();
}
