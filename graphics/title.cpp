#include "title.h"
#include "view.h"
#include <QMessageBox>

Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;

    this->setFocus();
    this->setSceneRect(0,0,width,height);
    view->sceneSet(this);

    QPixmap logo("/home/alestru/PetProjects/RPG/img/logo.png");

    QGraphicsPixmapItem* logoItem = new QGraphicsPixmapItem(logo);
\


    this->addItem(logoItem);
    logoItem->setPos(width / 2 - 100, height/2 - 100 - 100);

    startButton = new QPushButton(viewer);
    startButton->setText("Start Game");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(width/2 - 150, height / 2 , 300, 50));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));

    quitButton = new QPushButton(viewer);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(width/2 - 150, height / 2 + 100, 300, 50));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
}


void Title::quitProgram(){
    qApp->quit();
}
void Title::startGame(){
    gamewindow.getGame().setisGame(true);
    gamewindow.setSize();
    gamewindow.showFullScreen();
    emit closeWindow();
}

