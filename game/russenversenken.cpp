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
    connect(ui->pbtnPhase,SIGNAL(clicked()), this, SLOT(PhaseButtonClicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ReadyClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(SendClicked()));
    connect(ui->pbtnPlayerName, SIGNAL(clicked()), this, SLOT(NameClicked()));

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

void RussenVersenken::ReadyClicked() {
    if(phase==1 ){
        if(AllShipsAreSet() && isPlayersTurn==true){
            sendGrid();
            isPlayersTurn=false;
            ui->chat->insertPlainText("Deine Schiffe wurden gesetzt! Bitte warte bist du am Zug bist.\n");
            ui->chat->verticalScrollBar()->setValue(ui->chat->verticalScrollBar()->maximum());
        }else if(!AllShipsAreSet() && isPlayersTurn==true){
            ui->chat->insertPlainText("Bitte setze erst alle deine Schiffe bevor du bestätigst!\n");
            ui->chat->verticalScrollBar()->setValue(ui->chat->verticalScrollBar()->maximum());
        }
    }else if(phase==2){
        if(!isPlayersTurn){
            WebSocketClient::getInstance().sendPacket(153,"");
        }
    }else if(phase==3){

        WebSocketClient::getInstance().sendPacket(153,"");
        for (int i = 0; i < SHIPQUANTITY; ++i) {
            ships[i].CenterX =0;
            ships[i].CenterY =0;
            ships[i].length  =0;
            ships[i].rotation=0;
        }
        ui->chat->insertPlainText("Bitte setze deine Schiffe und Bestätige ihre Position mit dem \"Bereit\"-Knopf.");
    }
}
void RussenVersenken::NameClicked() {
   ui->label->setText(ui->lEditPlayerName->text());
   //ui->nameFrame->setEnabled(false);
   ui->nameFrame->close();

   WebSocketClient::getInstance().sendPacket(501,"{\"name\":\"" + ui->lEditPlayerName->text() + "\"}");
}

void RussenVersenken::PhaseButtonClicked(){
    if(phase==2){
        phase=0;
    }else{
        phase+=1;
    }
}

void RussenVersenken::SendClicked(){

    ui->chat->insertPlainText("Du: "+ui->sendText->text()+"\n");
    ui->chat->verticalScrollBar()->setValue(ui->chat->verticalScrollBar()->maximum());
    WebSocketClient::getInstance().sendPacket(601,"{\"ChatNachricht\":\"" + ui->sendText->text() + "\"}");

    ui->sendText->setText("");

}

void RussenVersenken::addChatmessage(QString m) {
    ui->chat->insertPlainText(m);
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
            if(PointInPolygon(pos,grid[i-1][j-1].hexagon.toPolygon())){
                x = i;
                y = j;
                return ;
            }
        }
    }
}

bool RussenVersenken::IsLegitPosition(int l,int x,int y ){
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


void RussenVersenken::SetShipParts(Ship ship){
     QList<QPoint> hexagons=GetShipHexagons(ship);

     foreach (QPoint p, hexagons) {
         grid[p.x()-1][p.y()-1].isShipPart=true;
     }
}


void RussenVersenken::ResetShipParts(Ship ship){
     QList<QPoint> hexagons=GetShipHexagons(ship);

     foreach (QPoint p, hexagons) {
         grid[p.x()-1][p.y()-1].isShipPart=false;
     }
}

bool RussenVersenken::IsNotOverlapping(Ship ship){
     QList<QPoint> hexagons=GetShipHexagons(ship);

     foreach (QPoint p, hexagons) {
         if(grid[p.x()-1][p.y()-1].isShipPart==true){
            return false;
         }
     }
     return true;
}

bool RussenVersenken::AllShipsAreSet(){
    for (int i = 0; i < SHIPQUANTITY; ++i) {
        if(ships[i].CenterX ==0 && ships[i].CenterY ==0 ){
            return false;
        }
    }
    return true;
}

QList<QPoint> RussenVersenken::GetShipHexagons(Ship ship){
    QList<QPoint> hexagons;
    hexagons.append(QPoint(ship.CenterX,ship.CenterY));

    if(ship.length>=2){
        QPoint tempP2=GetLeftNeighbourHexagon(ship.CenterX,ship.CenterY,ship.rotation);
        hexagons.append(tempP2);
        if(ship.length>=3){
            QPoint tempP3=GetRightNeighbourHexagon(ship.CenterX,ship.CenterY,ship.rotation);
            hexagons.append(tempP3);
            if(ship.length>=4){
                hexagons.append(GetLeftNeighbourHexagon(tempP2.x(),tempP2.y(),ship.rotation));
                if(ship.length>=5){
                     hexagons.append(GetRightNeighbourHexagon(tempP3.x(),tempP3.y(),ship.rotation));
                }
            }
        }
    }
    return hexagons;
}

QPoint RussenVersenken::GetLeftNeighbourHexagon(int x, int y, int r){
    QPoint p;
    switch (r) {
    case 0:
        p=QPoint(x-1,y);
        break;
    case 1:
        if(y%2==0){
            p=QPoint(x,y-1);
        }else{
            p=QPoint(x-1,y-1);
        }
        break;
    case 2:
        if(y%2==0){
            p=QPoint(x+1,y-1);
        }else{
            p=QPoint(x,y-1);
        }
        break;
    default:
        break;
    }

    return p;
}

QPoint RussenVersenken::GetRightNeighbourHexagon(int x, int y, int r){
    QPoint p;
    switch (r) {
    case 0:
        p=QPoint(x+1,y);
        break;
    case 1:
        if(y%2==0){
            p=QPoint(x+1,y+1);
        }else{
            p=QPoint(x,y+1);
        }
        break;
    case 2:
        if(y%2==0){
            p=QPoint(x,y+1);
        }else{
            p=QPoint(x-1,y+1);
        }
        break;
    default:
        break;
    }
    return p;
}

void RussenVersenken::keyPressEvent( QKeyEvent * event ){

    if(phase==1 && event->key() == Qt::Key_R ) {
        if(rotation!=2){
            rotation+=1;
        }else{
            rotation=0;
        }
        this->update();
    }

    if( event->key() == Qt::Key_D ){
        debug=!debug;
    }
}

void RussenVersenken::mouseReleaseEvent(QMouseEvent *event){


    int leftX = grid[0][0].hexagon.toPolygon().point(3).x();
    int rigthX = grid[9][9].hexagon.toPolygon().point(0).x();
    int topY = grid[0][0].hexagon.toPolygon().point(5).y();
    int bottomY = grid[9][9].hexagon.toPolygon().point(2).y();
    QRect rect = QRect(QPoint(leftX,topY),QPoint(rigthX,bottomY));
   // qDebug()<<event->pos();
    if(rect.contains(event->pos())){
        int x = -1;
        int y = -1;
        ClickedHexagon(x,y,event->pos());

        if(x>=0 && y>=0){

            if(phase==1){
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

                if(!IsLegitPosition(l,x,y)){
                    return;
                }

                Ship ship = Ship(l,x,y,rotation);

                if(IsNotOverlapping(ship)&& isPlayersTurn){
                    ResetShipParts(ships[shipCount]);

                    ships[shipCount]=ship;
                    SetShipParts(ship);
                }
            }else if(phase==2 ){
                if(!grid[x-1][y-1].isHit && isPlayersTurn){
                    grid[x-1][y-1].isHit=true;
                    isPlayersTurn=false;
                    sendHit(x-1,y-1);
                    ui->chat->insertPlainText("Du hast auf "+(QString)((char)(64+x))+(QString)((char)(48+y))+" geschossen\n");
                    ui->chat->verticalScrollBar()->setValue(ui->chat->verticalScrollBar()->maximum());
                    if(debug){
                        for (int i = 0; i < 10; ++i) {
                            for (int j = 0; j < 10; ++j) {
                                sendHit(i,j);
                            }
                        }
                    }
                }
            }
        }

    }

   // qDebug() << event->pos();
    this->update();
}


//debug feature start
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
//debug feature end

void RussenVersenken::createGrid(){

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j]= Hexagon(i+1,j+1);
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
            QPen gridPen;
            painter.save();
            painter.setPen(gridPen);
            painter.drawPolygon(grid[i-1][j-1].hexagon);
            painter.restore();

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

    painter.translate(1125 , 340);
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
    if(phase<2){

        int shipHeight=grid[0][0].hexagon.toPolygon().point(1).y()- grid[0][0].hexagon.toPolygon().point(0).y();

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

//---------------------------------------------------------------------
//drawing Hits
//---------------------------------------------------------------------
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {

            if(grid[i-1][j-1].isHit){

                QPoint line1Point1=grid[i-1][j-1].hexagon.toPolygon().point(0);
                QPoint line1Point2=grid[i-1][j-1].hexagon.toPolygon().point(3);
                QPoint line2Point1=grid[i-1][j-1].hexagon.toPolygon().point(1);
                QPoint line2Point2=grid[i-1][j-1].hexagon.toPolygon().point(4);
                QPen crossPen;
                crossPen.setWidth(5);

                if(grid[i-1][j-1].isShipPart){
                    crossPen.setColor(Qt::red);

                }else{
                    crossPen.setColor(Qt::gray);
                }

                painter.save();
                painter.setPen(crossPen);
                painter.drawLine(line1Point1,line1Point2);
                painter.drawLine(line2Point1,line2Point2);
                painter.restore();
            }
        }
    }
}


void RussenVersenken::sendGrid() {
    std::map<std::string, JSONUtils::Value> gridMap;
    int pos = 0;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            Hexagon hex = grid[j][i];
            gridMap.insert({std::to_string(pos) , std::to_string(hex.isShipPart) + "#"+std::to_string(hex.isHit)});
            pos++;
        }
    }
    QString message = QString::fromStdString(JSONUtils::generateJSON(gridMap));
    WebSocketClient::getInstance().sendPacket(151, message);
}

void RussenVersenken::sendHit(int x,int y) {

    QString message ="{\"x\":\"" +  QString::number(x) + "\",\"y\":\"" +  QString::number(y) + "\"}";
    WebSocketClient::getInstance().sendPacket(152, message);
}
