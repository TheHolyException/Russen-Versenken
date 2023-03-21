#include "hexagon.h"

Hexagon::Hexagon(){}

Hexagon::Hexagon(int x, int y) {
    hexagon = calculatePoly(x,y);
    isShipPart = false;
    isHit = false;
    centerX=x;
    centerY=y;


}

QList<QPointF> Hexagon::calcualtePolyPoints(int centerX,int centerY){
    QList<QPointF> points;
    for (int i=0;i<6;i++){

        QPointF p ;

        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180 * angle_deg;
        p.setX(centerX + RADIUS * cos(angle_rad));
        p.setY(centerY + RADIUS * sin(angle_rad));

        points.append(p);
    }
    return points;
}

/**
 * @brief Hexagon::calculatePoly calculating all 6 Points for the Hexagon
 * @param x CenterX
 * @param y CenterY
 * @return
 */
QPolygonF Hexagon::calculatePoly(int x, int y){

    int width =WIDTH;
    int height=HEIGHT;

    QList<QPointF> points;
    if(y%2==1){

        points = calcualtePolyPoints(width *x,height*y);
    }else{
        points = calcualtePolyPoints(width*x+width/2,height*y);
    }

    return QPolygonF(points);
}

