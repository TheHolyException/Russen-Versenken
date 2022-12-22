#ifndef MODEL_H
#define MODEL_H
#include "view.h"
#include <QObject>

class Model{
protected:
    View view;

public:
    Model();
    void update();
    void getState();
};

#endif // MODEL_H
