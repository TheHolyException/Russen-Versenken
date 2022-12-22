#ifndef RUSSENVERSENKEN_H
#define RUSSENVERSENKEN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class RussenVersenken; }
QT_END_NAMESPACE

class RussenVersenken : public QMainWindow
{
    Q_OBJECT

public:
    RussenVersenken(QWidget *parent = nullptr);
    ~RussenVersenken();

private:
    Ui::RussenVersenken *ui;
};
#endif // RUSSENVERSENKEN_H
