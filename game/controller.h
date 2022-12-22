#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"

class Controller : public QObject {
    Q_OBJECT
protected:
    View *view;
    Model *model;
public:
    Controller();
    void action();
};

#endif // CONTROLLER_H
