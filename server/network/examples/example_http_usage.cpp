#include "webserver.h" // WebServer
#include "routes/testroute.h" // TestRoute

int main() {
    // Create Server instance
    WebServer server;

    // Add a route
    // "/test" is the path to match
    // "GET" is the HTTP method to match
    // new TestRoute() is the route handler
    server.addRoute("/test", "GET", new TestRoute());

    // Start server on port 8080
    if (!server.start(8080)) {
        // If server failed to start, print error and exit
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return 0;
}