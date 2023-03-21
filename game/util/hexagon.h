#ifndef HEXAGON_H
#define HEXAGON_H

#include "qpolygon.h"
#include <QObject>

#define RADIUS 50
#define WIDTH  sqrt(3)*RADIUS;
#define HEIGHT int(1.5*(float)RADIUS);

class Hexagon {
public:
    Hexagon();
    Hexagon(int x, int y);
    QPolygonF hexagon;
    int centerX;
    int centerY;
    bool isShipPart;
    bool isHit;
private:
    QList<QPointF> calcualtePolyPoints(int centerX,int centerY);
    QPolygonF calculatePoly(int x, int y);
};

#endif // HEXAGON_H
