#include "russenversenken.h"

#include <QApplication>

#include "onlineclient.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    RussenVersenken w;
    w.show();

    OnlineClient client;
    client.start("localhost", 8888);

    return a.exec();
}
