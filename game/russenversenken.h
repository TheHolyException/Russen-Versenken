#ifndef RUSSENVERSENKEN_H
#define RUSSENVERSENKEN_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QMouseEvent>
#include "math.h"
#include "util/hexagon.h"
#include "qradiobutton.h"
#include "util/ship.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RussenVersenken; }
QT_END_NAMESPACE

class RussenVersenken : public QWidget
{
    Q_OBJECT

public:
    RussenVersenken(QWidget *parent = nullptr);
    ~RussenVersenken();
    void paintEvent(QPaintEvent *event) override;

    Hexagon grid[10][10];
    Ship ships[SHIPQUANTITY];
    QRadioButton *clickedRadioButton;

    bool PointInPolygon(QPoint point, QPolygon polygon);
    void ClickedHexagon(int &x,int &y, QPoint pos);

    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent( QKeyEvent * event ) override;

    bool IsLegitPosition(int l,int x,int y);
    bool NoShipAround(Ship ship);

    QList<QPoint> GetShipHexagons(Ship ship);
    QPoint GetLeftNeighbourHexagon(int x, int y, int r);
    QPoint GetRightNeighbourHexagon(int x, int y, int r);

    void SetShipParts(Ship ship);
    void ResetShipParts(Ship ship);
    bool IsNotOverlapping(Ship ship);


//debug feature
    QPoint calculateTextPoint(int x, int y);

public slots:
        void RadioButtonClicked();
private:
    Ui::RussenVersenken *ui;
    int rotation =0;
//    std::vector<std::vector<Hexagon>> gridPlayer1;
//    std::vector<std::vector<Hexagon>> gridPlayer2;


    void createGrid();
};
#endif // RUSSENVERSENKEN_H
