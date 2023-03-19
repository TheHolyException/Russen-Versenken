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
        network/socket/websocketserver.cpp \
        network/utils/jsonutils.cpp \
        network/utils/mariadb.cpp \
        network/utils/servercommanager.cpp \
        main.cpp \
        russenversenken_server.cpp \
        utils/csvinterface.cpp \
        utils/hexagon.cpp \
        utils/player.cpp  \

        
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    network/socket/websocketserver.h \
    network/utils/jsonutils.h \
    network/utils/mariadb.h \
    network/utils/servercommanager.h \
    russenversenken_server.h \
    utils/csvinterface.h \
    utils/hexagon.h \
    utils/player.h  \

