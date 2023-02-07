#include "webserver.h"

HttpServer::HttpServer(QObject *parent)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::addRoute(const QString &path, const QString &method, IRouteHandler *handler)
{
    m_routes[path] = {method, [handler](QTcpSocket *socket, const QMap<QString, QString> &parameters) {
        handler->handleRoute(socket, parameters);
    }};
}

bool HttpServer::start(quint16 port)
{
    return QTcpServer::listen(QHostAddress::Any, port);
}

QString HttpServer::errorString() const
{
    return QTcpServer::errorString();
}

void HttpServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor)) {
        connect(socket, &QTcpSocket::readyRead, [socket, this]() {
            // Parse the request
            QByteArray requestData = socket->readAll();
            QString requestString(requestData);
            QStringList requestLines = requestString.split("\r\n");
            if (requestLines.empty())
                return;

            // Parse the request line
            QStringList requestLineTokens = requestLines[0].split(" ");
            if (requestLineTokens.size() != 3)
                return;

            // Parse the request line
            QString method = requestLineTokens[0];
            QString path = requestLineTokens[1];
            QString httpVersion = requestLineTokens[2];

            // Parse the headers
            QMap<QString, QString> headers;
            for (int i = 1; i < requestLines.size(); ++i) {
                QString line = requestLines[i];
                int index = line.indexOf(":");
                if (index != -1) {
                    QString key = line.left(index).trimmed();
                    QString value = line.mid(index + 1).trimmed();
                    headers[key] = value;
                }
            }



            // Handle the request
            auto it = m_routes.find(path);
            if (it != m_routes.end()) {
                Route route = it.value();

                if (WSUtils::isAllowedMethod(route.method) && route.method == method) {
                    route.callback(socket, headers);
                } else {
                    std::string response = WSUtils::createJSONResponse("{\"Code\": \"405\", \"Message\": \"Method Not Allowed\"}");
                    socket->write(response.c_str());
                    socket->close();
                }
            } else {
                std::string response = WSUtils::createJSONResponse("{\"Code\": \"404\", \"Message\": \"Not Found\"}");
                socket->write(response.c_str());
                socket->close();
            } });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    } else {
        delete socket;
    }
}
