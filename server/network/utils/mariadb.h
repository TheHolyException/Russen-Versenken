#ifndef MARIADB_H
#define MARIADB_H

#include <QtSql>

/**
 * @class MariaDB
 * @brief A class for connecting to and interacting with a MariaDB database.
 *
 * The MariaDB class allows you to connect to a MariaDB database, execute queries, and manage transactions.
 * 
 * @note 
 * When building and running the project for the first time you might encounter the following error:
 * ```
 * QSqlDatabase: QMYSQL driver not loaded
 * QSqlDatabase: available drivers: QSQLITE QODBC QPSQL
 * Error opening database: "Driver not loaded Driver not loaded"
 * ```
 * The Qt Company does not provide a pre-built QMYSQL driver for Windows, so you will have to build them yourself or use my prebuilt Dlls.
 * To build them yourself, follow the instructions on the [Qt Wiki](https://doc.qt.io/qt-6/sql-driver.html).
 * To download my prebuilt Dlls, go to the /Source/Dlls/sqldrivers and copy the files inside sqldrivers into **C:\Qt\6.4.1\mingw_64\plugins\sqldrivers**. 
 */
class MariaDB
{
public:
    /**
     * @brief Constructs a new MariaDB object with the given connection details.
     * @param hostname The hostname or IP address of the MariaDB server.
     * @param username The username to use for authentication.
     * @param password The password to use for authentication.
     * @param database The name of the database to connect to.
     * @param port The port number to use for the connection (default: 3306).
     * @example example_mariadb_usage.cpp
     */
    MariaDB(const QString &hostname, const QString &username, const QString &password, const QString &database, int port = 3306);

    /**
     * @brief Destroys the MariaDB object and closes the database connection.
     */
    ~MariaDB();

    /**
     * @brief Opens a connection to the MariaDB database.
     * @return true if the connection was successfully established, false otherwise.
     */
    bool open();

    /**
     * @brief Closes the connection to the MariaDB database.
     */
    void close();

    /**
     * @brief Executes a SQL query on the MariaDB database.
     * @param query The SQL query to execute.
     * @return A QSqlQuery object that can be used to iterate over the query results.
     */
    QSqlQuery exec(const QString &query);

    /**
     * @brief Begins a transaction on the MariaDB database.
     * @return true if the transaction was successfully started, false otherwise.
     */
    bool transaction();

    /**
     * @brief Commits a transaction on the MariaDB database.
     * @return true if the transaction was successfully committed, false otherwise.
     */
    bool commit();

    /**
     * @brief Rolls back a transaction on the MariaDB database.
     * @return true if the transaction was successfully rolled back, false otherwise.
     */
    bool rollback();

    /**
     * @brief Prints the contents of a table to the console in a table-like format.
     * @param tableName The name of the table to print.
     */
    void
    printDebugTable(const QString &tableName);

    /**
     * @brief Returns the QSqlDatabase object being used by the MariaDB class.
     * @return The QSqlDatabase object.
     */
    QSqlDatabase getM_DB();

private:
    /**
     * @brief The hostname of the MariaDB server.
     */
    QString m_hostname;

    /**
     * @brief The username to use when connecting to the MariaDB server.
     */
    QString m_username;

    /**
     * @brief The password to use when connecting to the MariaDB server.
     */
    QString m_password;

    /**
     * @brief The name of the database to use.
     */
    QString m_database;

    /**
     * @brief The port to use when connecting to the MariaDB server.
     */
    int m_port;

    /**
     * @brief The QSqlDatabase object used to manage the connection to the MariaDB server.
     */
    QSqlDatabase m_db;
};

#endif // MARIADB_H
