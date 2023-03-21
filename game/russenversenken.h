#ifndef RUSSENVERSENKEN_H
#define RUSSENVERSENKEN_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QMouseEvent>
#include <QScrollBar>
#include "math.h"
#include "util/hexagon.h"
#include "qradiobutton.h"
#include "util/ship.h"
#include "websocketclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RussenVersenken; }
QT_END_NAMESPACE

class RussenVersenken : public QWidget
{
    Q_OBJECT

public:
    static RussenVersenken *getInstance()
    {

        if (!m_instance) {
           m_instance = new RussenVersenken();
        }
        return m_instance;
    }

    Hexagon grid[10][10];
    int phase=0;
    bool isPlayersTurn=true;
    Ui::RussenVersenken *ui;

    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent( QKeyEvent * event ) override;

    void addChatmessage(QString m);

private slots:
        void RadioButtonClicked();
        void ReadyClicked();
        void SendClicked();
        void NameClicked();
private:

    Ship ships[SHIPQUANTITY];
    QRadioButton *clickedRadioButton;
    int rotation = 0;
    bool debug = false;
    inline static RussenVersenken *m_instance;

    RussenVersenken(QWidget *parent = nullptr);
    ~RussenVersenken();

    bool PointInPolygon(QPoint point, QPolygon polygon);
    void ClickedHexagon(int &x,int &y, QPoint pos);

    QList<QPoint> GetShipHexagons(Ship ship);
    QPoint GetLeftNeighbourHexagon(int x, int y, int r);
    QPoint GetRightNeighbourHexagon(int x, int y, int r);

    void SetShipParts(Ship ship);
    void ResetShipParts(Ship ship);
    bool IsNotOverlapping(Ship ship);
    bool AllShipsAreSet();
    bool IsLegitPosition(int l,int x,int y);

    void sendGrid();
    void sendHit(int x,int y);

    //debug feature
        QPoint calculateTextPoint(int x, int y);


    void createGrid();
};
#endif // RUSSENVERSENKEN_H
