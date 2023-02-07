#ifndef HTTPTESTROUTE_H
#define HTTPTESTROUTE_H

#include "iroutehandler.h"
#include "../utils/ws_utils.h"

class HTTPTestRoute  : public IRouteHandler
{
public:
    HTTPTestRoute();
    void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) override;
};

#endif // HTTPTESTROUTE_H
