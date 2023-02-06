#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug("Hello World");
    Server server;

    return a.exec();
}

