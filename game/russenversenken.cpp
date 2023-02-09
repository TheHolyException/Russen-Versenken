#include "russenversenken.h"
#include "ui_russenversenken.h"

using namespace std;


RussenVersenken::RussenVersenken(QWidget *parent) : QMainWindow(parent) , ui(new Ui::RussenVersenken) {
    ui->setupUi(this);

    createGrids();
}

RussenVersenken::~RussenVersenken() {
    delete ui;
}

QPoint RussenVersenken::calculateTextPoint(int x, int y){

    int width =sqrt(3)*RADIUS;
    int height=int(1.5*(float)RADIUS);

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

void RussenVersenken::createGrids(){

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            gridPlayer1[i][j]= Hexagon(i+1,j+1);
            gridPlayer2[i][j] = Hexagon(i+1,j+1);
        }
    }
}

void RussenVersenken:: paintEvent(QPaintEvent * /* event */){

    QPainter painter(this);

    painter.eraseRect(0,0,1280,1024);

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {

            QPoint point = calculateTextPoint(i,j);
            QString s = QString::number(i,10)+","+QString::number(j,10);
            painter.drawText(point,s);

            painter.drawPolygon(gridPlayer1[i-1][j-1].hexagon);
        }
    }
    float width = WIDTH;
    float height = HEIGHT;
    for (int var = 0; var < 10; var++) {
         painter.drawText((width-3-0.6*var+width*var), 15,(QString)((char)(65+var)));
         painter.drawText((width*1.5-3-0.6*var+width*var), height*11,(QString)((char)(65+var)));
         if(var==9){
          painter.drawText(25,height+height*var,"10");
          painter.drawText(width*11+10,height+height*var,"10");
          continue;
         }
         painter.drawText(25,height+height*var,(QString)((char)(49+var)));
         painter.drawText(width*11+10,height+height*var,(QString)((char)(49+var)));
    }

}
