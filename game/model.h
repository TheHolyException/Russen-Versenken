#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "view.h"

class Model : public QObject {
protected:
    View *view;

public:
    Model();
    void update();
    int getState();
};

#endif // MODEL_H
