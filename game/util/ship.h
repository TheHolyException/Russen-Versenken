#ifndef SHIP_H
#define SHIP_H

#define SHIPQUANTITY 5

#include <QObject>

class Ship {
public:
    Ship();
    Ship(int l,int x,int y,int r);
    int length;
    int CenterX;
    int CenterY;
    int rotation;
};

#endif // SHIP_H
