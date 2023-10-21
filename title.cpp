#include "title.h"
#include <QMessageBox>

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;
    /*viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);*/

    /*background = new AnimatedGraphicsItem;
    background->setPixmap(QPixmap(":/images/background.png"));
    foreground = new QGraphicsPixmapItem(QPixmap(":/images/title.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));

    animation = new QPropertyAnimation(background, "pos");
    animation->setLoopCount(-1);
    animation->setDuration(150000);
    animation->setStartValue(QPoint(-width,0));
    animation->setEndValue(QPoint(0,0));
    animation->start();

    logo->setPos((width - logo->boundingRect().width()) / 2, height / 12);
    addItem(background);
    addItem(foreground);
    addItem(logo);*/
    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);

    //Push Button to start
    startButton = new QPushButton(viewer);
    startButton->setText("Start Game");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(640-300/2, 696 / 2 - 100 , 300, 50));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    //Push Button to quit
    quitButton = new QPushButton(viewer);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(640-300/2, 696 / 2 + 100, 300, 50));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
}


void Title::quitProgram(){
    qApp->quit();
}
void Title::startGame(){
    gamewindow.setSize();
    gamewindow.show();
}

