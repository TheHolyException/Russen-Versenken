#include "ws_utils.h"

WSUtils::WSUtils()
{
}

QStringList WSUtils::m_allowedMethods = {"GET", "POST", "PUT", "DELETE"};

std::string WSUtils::createJSONResponse(std::string p_content) {
    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: application/json\r\n";
    oss << "Content-Length: " << p_content.length() << "\r\n";
    oss << "\r\n";
    oss << p_content;

    return oss.str();
}

std::string WSUtils::createHTMLResponse(std::string p_content) {
    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << p_content.length() << "\r\n";
    oss << "\r\n";
    oss << p_content;

    return oss.str();
}

bool WSUtils::isAllowedMethod(const QString &method) {
    return m_allowedMethods.contains(method, Qt::CaseInsensitive);
}
