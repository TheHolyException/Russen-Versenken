#include "russenversenken.h"
#include "ui_russenversenken.h"


using namespace std;


RussenVersenken::RussenVersenken(QWidget *parent) : QWidget(parent) , ui(new Ui::RussenVersenken) {
    ui->setupUi(this);
    connect(ui->rbtn2er,SIGNAL(clicked()), this, SLOT(RadioButtonClicked()));
    connect(ui->rbtn3er,SIGNAL(clicked()), this, SLOT(RadioButtonClicked()));
    connect(ui->rbtn3er2,SIGNAL(clicked()), this, SLOT(RadioButtonClicked()));
    connect(ui->rbtn4er,SIGNAL(clicked()), this, SLOT(RadioButtonClicked()));
    connect(ui->rbtn5er,SIGNAL(clicked()), this, SLOT(RadioButtonClicked()));


    createGrid();

    clickedRadioButton= ui->rbtn2er;

    for (int var = 0; var < SHIPQUANTITY; ++var) {
        ships[var].CenterX =0;
        ships[var].CenterY =0;
        ships[var].length  =0;
        ships[var].rotation=0;
    }
}

RussenVersenken::~RussenVersenken() {
    delete ui;
}

void RussenVersenken::RadioButtonClicked(){
    clickedRadioButton = (QRadioButton*)sender();
}

bool RussenVersenken::PointInPolygon(QPoint point, QPolygon polygon) {

  int i, j, nvert = polygon.size();
  bool c = false;
  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
      if( ( (polygon.point(i).y() >= point.y() ) != (polygon.point(j).y() >= point.y()) ) &&
            (point.x() <= (polygon.point(j).x() - polygon.point(i).x()) * (point.y() - polygon.point(i).y()) /
            (polygon.point(j).y() - polygon.point(i).y()) + polygon.point(i).x())
      )
      c = !c;
  }
  return c;
}

void RussenVersenken::ClickedHexagon(int &x,int &y, QPoint pos){
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if(PointInPolygon(pos,gridPlayer[i-1][j-1].hexagon.toPolygon())){
                x = i;
                y = j;
                return ;
            }
        }
    }
}

bool RussenVersenken::isLegitPosition(int l,int x,int y ){
    switch (rotation) {
    case 0:
        switch (l) {
        case 2:
            if(2<=x && x<=10){
                return true;
            }
            break;
        case 3:
            if(2<=x && x<=9){
                return true;
            }
            break;
        case 4:
            if(3<=x && x<=9){
                return true;
            }
            break;
        case 5:
            if(3<=x && x<=8){
                return true;
            }
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (l) {
        case 2:
            if(y%2==0){
                if(((1<=x && x<=10)&& (y>=2 && y<=10))){
                    return true;
                }
            }else{
                if(((2<=x && x<=10)&& (y>=2 && y<=10))){
                    return true;
                }
            }
            break;
        case 3:
            if(y%2==0){
                if(((1<=x && x<=9)&& (y>=2 && y<=9))){
                    return true;
                }
            }else{
                if(((2<=x && x<=10)&& (y>=2 && y<=9))){
                    return true;
                }
            }
            break;
        case 4:
            if(y%2==0){
                if(((2<=x && x<=9)&& (y>=3 && y<=9))){
                    return true;
                }
            }else{
                if(((2<=x && x<=10)&& (y>=3 && y<=9))){
                    return true;
                }
            }
            break;
        case 5:
            if(y%2==0){
                if(((2<=x && x<=9)&& (y>=3 && y<=8))){
                    return true;
                }
            }else{
                if(((2<=x && x<=9)&& (y>=3 && y<=8))){
                    return true;
                }
            }
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (l) {
        case 2:
            if(y%2==0){
                if(((1<=x && x<=9)&& (y>=2 && y<=10))){
                    return true;
                }
            }else{
                if(((1<=x && x<=10)&& (y>=2 && y<=10) && !(x==1&& y==1))){
                    return true;
                }
            }
            break;
        case 3:
            if(y%2==0){
                if(((1<=x && x<=9)&& (y>=2 && y<=9))){
                    return true;
                }
            }else{
                if(((2<=x && x<=10)&& (y>=2 && y<=9))){
                    return true;
                }
            }
            break;
        case 4:
            if(y%2==0){
                if(((1<=x && x<=9) && (y>=3 && y<=9) && !(x==1 && (y==1 ||y==3)))){
                    return true;
                }
            }else{
                if(((2<=x && x<=9)&& (y>=3 && y<=9))){
                    return true;
                }
            }
            break;
        case 5:
            if(y%2==0){
                if(((2<=x && x<=9)&& (y>=3 && y<=8))){
                    return true;
                }
            }else{
                if(((2<=x && x<=9)&& (y>=3 && y<=8))){
                    return true;
                }
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }


    return false;
}




void RussenVersenken::keyPressEvent( QKeyEvent * event ){
    if( event->key() == Qt::Key_R )
    {
        if(rotation!=2){
            rotation+=1;
        }else{
            rotation=0;
        }
        this->update();
    }

}

void RussenVersenken::mouseReleaseEvent(QMouseEvent *event){
    int leftX = gridPlayer[0][0].hexagon.toPolygon().point(3).x();
    int rigthX = gridPlayer[9][9].hexagon.toPolygon().point(0).x();
    int topY = gridPlayer[0][0].hexagon.toPolygon().point(5).y();
    int bottomY = gridPlayer[9][9].hexagon.toPolygon().point(2).y();
    QRect rect = QRect(QPoint(leftX,topY),QPoint(rigthX,bottomY));
    if(rect.contains(event->pos())){
        int x = -1;
        int y = -1;
        ClickedHexagon(x,y,event->pos());

        int l = 0;
        int shipCount=0;

        if(clickedRadioButton->objectName()=="rbtn2er"){
            shipCount=0;
            l=2;
        }else if(clickedRadioButton->objectName()=="rbtn3er"){
            shipCount=1;
            l=3;
        }else if(clickedRadioButton->objectName()=="rbtn3er2"){
            shipCount=2;
            l=3;
        }else if(clickedRadioButton->objectName()=="rbtn4er"){
            shipCount=3;
            l=4;
        }else if(clickedRadioButton->objectName()=="rbtn5er"){
            shipCount=4;
            l=5;
        }

       if(!isLegitPosition(l,x,y)){
           return;
       }
        if(x>=0 && y>=0){
            Ship ship = Ship(l,x,y,rotation);

            ships[shipCount]=ship;
        }
    }   

   // qDebug() << event->pos();
    this->update();
}


//debug feature start
//QPoint RussenVersenken::calculateTextPoint(int x, int y){

//    int width =sqrt(3)*RADIUS;
//    int height=int(1.5*(float)RADIUS);

//    QPoint point;
//    point.setY(height*y);

//    if(y%2==1){
//        point.setX(width*x);
//    }else
//    {
//        point.setX(width*x+width/2);
//    }
//    return point;
//}
//debug feature end

void RussenVersenken::createGrid(){

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            gridPlayer[i][j]= Hexagon(i+1,j+1);
        }
    }
}

void RussenVersenken:: paintEvent(QPaintEvent * /* event */){

    QPainter painter(this);
    int width=WIDTH;
    float height = HEIGHT;

    painter.eraseRect(0,0,1280,1024);

//---------------------------------------------------------------------
// drawing Hexagon Grid
//---------------------------------------------------------------------

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {

            //debug feature start
//            QPoint point = calculateTextPoint(i,j);
//            QString s = QString::number(i,10)+","+QString::number(j,10);
//            painter.drawText(point,s);
            //debug feature end

            painter.drawPolygon(gridPlayer[i-1][j-1].hexagon);
        }
    }

//---------------------------------------------------------------------
// drawing Grid Label
//---------------------------------------------------------------------

    for (int var = 0; var < 10; var++) {
         painter.drawText((var+1)*width-3, 15,(QString)((char)(65+var)));
         painter.drawText((var+1)*width+(width/2)-3, height*11,(QString)((char)(65+var)));
         if(var==9){
          painter.drawText(25,height*(var+1),"10");
          painter.drawText(width*11+10,height*(var+1),"10");
          continue;
         }
         painter.drawText(25,height*(var+1),(QString)((char)(49+var)));
         painter.drawText(width*11+10,height*(var+1),(QString)((char)(49+var)));
    }


//---------------------------------------------------------------------
// Drawing Rotation Display
//---------------------------------------------------------------------
    painter.save();
    QRect rect = QRect(-60,-15,120,30);

    QPainterPath path;
    path.addRect(rect);

    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    painter.translate(1100 , 340);
    switch (rotation) {
    case 0:
        painter.rotate(0.0);
        break;
    case 1:
        painter.rotate(60.0);
        break;
    case 2:
        painter.rotate(120.0);
        break;
    default:
        break;
    }
    painter.drawRect(rect);
    painter.fillPath(path, brush);

    painter.restore();

//---------------------------------------------------------------------
//drawing ships
//---------------------------------------------------------------------
    int shipHeight=gridPlayer[0][0].hexagon.toPolygon().point(1).y()- gridPlayer[0][0].hexagon.toPolygon().point(0).y();

    for (int var = 0; var < SHIPQUANTITY; ++var) {
        int l= ships[var].length;
        if(l>=2&& l<=5){
            int x=ships[var].CenterX;
            int y=ships[var].CenterY;
            int r=ships[var].rotation;

            painter.save();

            int lShift=(l==2||l==4)?1:0;

            QRect shipRect = QRect(-(width*l)/2-(width/2)*lShift,-shipHeight/2,width*l,shipHeight);

            QPainterPath shipPath;
            shipPath.addRect(shipRect);

            QBrush shipBrush;
            shipBrush.setColor(Qt::black);
            shipBrush.setStyle(Qt::SolidPattern);
            int yShift= y%2==1?0:1;

            painter.translate(x*width+(width/2)*yShift, y*height);
            switch (r) {
            case 0:
                painter.rotate(0.0);
                break;
            case 1:
                painter.rotate(60.0);
                break;
            case 2:
                painter.rotate(120.0);
                break;
            default:
                break;
            }

            painter.drawRect(shipRect);
            painter.fillPath(shipPath, shipBrush);

            painter.restore();

        }
    }
}
