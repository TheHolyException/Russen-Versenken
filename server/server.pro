QT -= gui
QT += network
QT += sql
QT += websockets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        network/routes/httptestroute.cpp \
        network/routes/jsontestroute.cpp \
        network/socket/websocketserver.cpp \
        network/utils/jsonutils.cpp \
        network/utils/mariadb.cpp \
        network/utils/servercommanager.cpp \
        network/utils/ws_utils.cpp \
        network/ws/webserver.cpp \
        main.cpp \
        russenversenken_server.cpp \
        util/hexagon.cpp \
        util/player.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    network/routes/httptestroute.h \
    network/routes/iroutehandler.h \
    network/routes/jsontestroute.h \
    network/socket/websocketserver.h \
    network/utils/jsonutils.h \
    network/utils/mariadb.h \
    network/utils/servercommanager.h \
    network/utils/ws_utils.h \
    network/ws/webserver.h \
    russenversenken_server.h \
    util/hexagon.h \
    util/player.h
