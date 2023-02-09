#ifndef RUSSENVERSENKEN_H
#define RUSSENVERSENKEN_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include "math.h"
#include "util/hexagon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RussenVersenken; }
QT_END_NAMESPACE

class RussenVersenken : public QMainWindow
{
    Q_OBJECT

public:
    RussenVersenken(QWidget *parent = nullptr);
    ~RussenVersenken();
    void paintEvent(QPaintEvent *event) override;
    QPoint calculateTextPoint(int x, int y);
    Hexagon gridPlayer1[10][10];
    Hexagon gridPlayer2[10][10];


private:
    Ui::RussenVersenken *ui;
//    std::vector<std::vector<Hexagon>> gridPlayer1;
//    std::vector<std::vector<Hexagon>> gridPlayer2;


    void createGrids();
};
#endif // RUSSENVERSENKEN_H
