#ifndef RUSSENVERSENKEN_H
#define RUSSENVERSENKEN_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include "math.h"

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
    QList<QPoint> calcualtePoints(int centerX, int centerY,int radius);
    QPolygon calculatePoly(int x, int y,int radius);
    QPoint calculateTextPoint(int x, int y,int radius);


private:
    Ui::RussenVersenken *ui;
};
#endif // RUSSENVERSENKEN_H
