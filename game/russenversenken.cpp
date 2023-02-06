#include "russenversenken.h"
#include "ui_russenversenken.h"




RussenVersenken::RussenVersenken(QWidget *parent) : QMainWindow(parent) , ui(new Ui::RussenVersenken) {
    ui->setupUi(this);
}

RussenVersenken::~RussenVersenken() {
    delete ui;
}

QList<QPoint> RussenVersenken::calcualtePoints(int centerX,int centerY,int radius){
    QList<QPoint> points;
    for (int i=0;i<6;i++){

        QPoint p ;

        float angle_deg = 60 * i - 30;
        float angle_rad = M_PI / 180 * angle_deg;
        p.setX(centerX + radius * cos(angle_rad));
        p.setY(centerY + radius * sin(angle_rad));

//        p.setX(center + radius*cos(i*M_PI/3));
//        p.setY(center + radius*sin(i*M_PI/3));

        points.append(p);
    }
    return points;
}

QPolygon RussenVersenken::calculatePoly(int x, int y,int radius){

    int width =sqrt(3)*radius;
    int height=int(1.5*(float)radius);

    QList<QPoint> points;
    if(y%2==1){

        points= calcualtePoints(width*x,height*y,radius);
    }else
    {
        points= calcualtePoints(width*x+width/2,height*y,radius);
    }
    return QPolygon(points);
}
QPoint RussenVersenken::calculateTextPoint(int x, int y,int radius){

    int width =sqrt(3)*radius;
    int height=int(1.5*(float)radius);

    QPoint point;
    point.setY(height*y);

    if(y%2==1){
        point.setX(width*x);
    }else
    {
        point.setX(width*x+width/2);
    }
    return point;
}

void RussenVersenken:: paintEvent(QPaintEvent * /* event */){

    QPainter painter(this);

    int radius = 50;


    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {

            QPolygon poly = calculatePoly(i,j,radius);
            QPoint point = calculateTextPoint(i,j,radius);
            QString s = QString::number(i,10)+","+QString::number(j,10);
            painter.drawText(point,s);
            painter.drawPolygon(poly);
        }
    }
}
