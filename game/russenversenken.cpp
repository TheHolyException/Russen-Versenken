#include "russenversenken.h"
#include "ui_russenversenken.h"

RussenVersenken::RussenVersenken(QWidget *parent) : QMainWindow(parent) , ui(new Ui::RussenVersenken) {
    ui->setupUi(this);
}

RussenVersenken::~RussenVersenken() {
    delete ui;
}

