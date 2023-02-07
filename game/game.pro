QT += core gui
QT += network
QT += websockets
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    main.cpp \
    model.cpp \
    russenversenken.cpp \
    util/jsonutils.cpp \
    util/playercommanager.cpp \
    view.cpp \
    websocketclient.cpp

HEADERS += \
    model.h \
    controller.h \
    russenversenken.h \
    util/jsonutils.h \
    util/playercommanager.h \
    view.h \
    websocketclient.h

FORMS += \
    russenversenken.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
