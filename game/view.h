#ifndef VIEW_H
#define VIEW_H

#include <QObject>

class View {
    Q_OBJECT

public:
    View();
    virtual void update();
    virtual void notify();
};

#endif // VIEW_H
