#ifndef WS_UTILS_H
#define WS_UTILS_H

#include <QString>
#include <QObject>

#include <iostream>
#include <sstream> // std::ostringstream

/**
 * @class WSUtils
 * @brief Utility class for handling web server related tasks
 *
 * This class provides static methods for creating HTTP responses in the form of JSON or HTML, as well as a method for checking if a given HTTP request method is allowed.
 */
class WSUtils : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a new WSUtils object.
     */
    WSUtils();

    /**
     * @brief Creates a JSON HTTP response with the given content
     * @param p_content The content to include in the response
     * @return The JSON HTTP response as a string
     */
    static std::string createJSONResponse(std::string p_content);

    /**
     * @brief Creates an HTML HTTP response with the given content
     * @param p_content The content to include in the response
     * @return The HTML HTTP response as a string
     */
    static std::string createHTMLResponse(std::string p_content);

    /**
     * @brief Checks if the given HTTP request method is allowed
     * @param method The HTTP request method to check
     * @return True if the method is allowed, false otherwise
     */
    static bool isAllowedMethod(const QString &method);

private:
    /**
     * @brief List of allowed HTTP request methods
     */
    static QStringList m_allowedMethods;
};

#endif // WS_UTILS_H
