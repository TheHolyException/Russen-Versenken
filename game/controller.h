#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"

class Controller {
    Q_OBJECT
public:
    Controller();
protected:
    View view;
};

#endif // CONTROLLER_H
