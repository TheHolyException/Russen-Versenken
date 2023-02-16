#ifndef HEXAGON_H
#define HEXAGON_H

#include <QObject>


class Hexagon
{
public:
    Hexagon();
    Hexagon(int x, int y);
    int centerX;
    int centerY;
    bool isShipPart;
    bool isHit;
};

#endif // HEXAGON_H
