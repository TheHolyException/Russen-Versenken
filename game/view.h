#ifndef VIEW_H
#define VIEW_H

#include <QObject>

class Model;
class Controller;

class View : public QObject {
    Q_OBJECT

protected:
    Model *model;
    Controller *controller;

public:
    View();
    virtual void update();
    virtual void notify();
};


#endif // VIEW_H
