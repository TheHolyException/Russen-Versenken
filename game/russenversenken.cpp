#include "russenversenken.h"
#include "ui_russenversenken.h"




RussenVersenken::RussenVersenken(QWidget *parent) : QMainWindow(parent) , ui(new Ui::RussenVersenken) {
    ui->setupUi(this);
}

RussenVersenken::~RussenVersenken() {
    delete ui;
}

QList<QPoint> RussenVersenken::calcualtePoints(int center,int radius){
    QList<QPoint> points;
    for (int i=0;i<6;i++){

        QPoint p ;
        p.setX(center + radius*cos(i*M_PI/3));
        p.setY(center + radius*sin(i*M_PI/3));

        points.append(p);
    }
    return points;
}

void RussenVersenken:: paintEvent(QPaintEvent * /* event */){

    QPainter painter(this);

    int radius = 50;

    QList<QPoint> points= calcualtePoints(radius,radius);
    QPolygon poly = QPolygon(points);

    painter.drawPolygon(poly);

}
