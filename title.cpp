#include "title.h"
#include <QMessageBox>

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;

    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);


    startButton = new QPushButton(viewer);
    startButton->setText("Start Game");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(640-300/2, 696 / 2 - 100 , 300, 50));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));

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

