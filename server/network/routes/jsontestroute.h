#ifndef JSONTESTROUTE_H
#define JSONTESTROUTE_H

#include "iroutehandler.h"
#include "../utils/jsonutils.h"
#include "../utils/ws_utils.h"

class JSONTestRoute : public IRouteHandler
{
public:
    JSONTestRoute();
    void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) override;
};

#endif // JSONTESTROUTE_H
