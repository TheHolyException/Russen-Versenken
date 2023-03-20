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

    void paintEvent(QPaintEvent *event) override;

    Hexagon grid[10][10];
    Ship ships[SHIPQUANTITY];
    QRadioButton *clickedRadioButton;
    int phase=0;
    bool isPlayersTurn=true;
    Ui::RussenVersenken *ui;

    bool PointInPolygon(QPoint point, QPolygon polygon);
    void ClickedHexagon(int &x,int &y, QPoint pos);

    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent( QKeyEvent * event ) override;

    bool IsLegitPosition(int l,int x,int y);

    QList<QPoint> GetShipHexagons(Ship ship);
    QPoint GetLeftNeighbourHexagon(int x, int y, int r);
    QPoint GetRightNeighbourHexagon(int x, int y, int r);

    void SetShipParts(Ship ship);
    void ResetShipParts(Ship ship);
    bool IsNotOverlapping(Ship ship);
    bool AllShipsAreSet();

    void addChatmessage(QString m);
    void sendGrid();
    void sendHit(int x,int y);

//debug feature
    QPoint calculateTextPoint(int x, int y);

public slots:
        void RadioButtonClicked();
        void PhaseButtonClicked();
        void ReadyClicked();
        void SendClicked();
        void NameClicked();
private:
    RussenVersenken(QWidget *parent = nullptr);
    ~RussenVersenken();

    int rotation =0;
    bool debug=false;
    inline static RussenVersenken *m_instance;
//    std::vector<std::vector<Hexagon>> gridPlayer1;
//    std::vector<std::vector<Hexagon>> gridPlayer2;


    void createGrid();
};
#endif // RUSSENVERSENKEN_H
