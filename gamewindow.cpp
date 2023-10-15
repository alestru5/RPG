#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene();
    hero = new Hero();
    this->resize(1680, 1050);
    this->setFixedSize(1680, 1050);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-250, -250, 500, 500);
    scene->addLine(-800, 0, 800, 0, QPen(Qt::black));
    scene->addLine(0, 450, 0, -450, QPen(Qt::black));

    scene->addLine(-800, -450, 800, -450, QPen(Qt::black));
    scene->addLine(-800, 450, 800, 450, QPen(Qt::black));
    scene->addLine(-800, -450, -800, 450, QPen(Qt::black));
    scene->addLine(800, -450, 800, 450, QPen(Qt::black));

    scene->addItem(hero);
    hero->setPos(QPoint(0, 0));
}

GameWindow::~GameWindow() {
    delete ui;
}
