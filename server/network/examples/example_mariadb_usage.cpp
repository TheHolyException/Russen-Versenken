#include "mariadb.h"

int main() {
    // Database Connection
    MariaDB db("ip", "username", "password", "database");

    // Check if connection was successful
    if (!db.open()) {
        // If not, print error and exit
        qCritical() << "Error opening database:" << db.getM_DB().lastError().text();

        // Exit with error code 1
        return 1;
    } else {
        // If yes, print success message (not necessary)
        std::cout << "Connected to DB" << std::endl;
    }

    // Sending a query to the database
    QSqlQuery query = db.exec("SELECT * FROM test_table;"); // SQL query to execute

    // Print last error (if any)
    qDebug() << db.getM_DB().lastError().text();

    // Iterate over the query results
    while (query.next()) {
        // Get the first column of the current row
        QString tableName = query.value(0).toString();

        // Print the value of the first column
        qDebug() << tableName;
    }

    // Print the content of the table "test_table" to the console (for debugging)
    db.printDebugTable("test_table");

    // Close the connection to the database
    db.close();
}