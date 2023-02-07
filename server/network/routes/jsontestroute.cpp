#include "jsontestroute.h"

JSONTestRoute::JSONTestRoute() { }

void JSONTestRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    std::map<std::string, JSONUtils::Value> data{
      {"code", 200},
      {"message", "JSON Generator works!"},
      {"bool test", true}
    };
    std::string json = JSONUtils::generateJSON(data);
    std::string response = WSUtils::createJSONResponse(json);

    socket->write(response.c_str());
    socket->close();
}
