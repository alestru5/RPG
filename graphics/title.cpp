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
    startButton->setText("New Game");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(width/2 - 150, height / 2 -50, 300, 50));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));

    continueButton = new QPushButton(viewer);
    continueButton->setText("Continue Game");
    continueButton->setObjectName(QString("continueButton"));
    continueButton->setToolTip("Continue Game");
    continueButton->setGeometry(QRect(width/2 - 150, height / 2 + 10, 300, 50));
    connect(continueButton, SIGNAL(clicked()), this, SLOT(continueGame()));

    quitButton = new QPushButton(viewer);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(width/2 - 150, height / 2 + 70, 300, 50));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));

    connect(&gamewindow, &GameWindow::quitGame, this, &Title::quitGame);
}


void Title::quitProgram(){
    qApp->quit();
}
void Title::startGame(){
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/Maps/NewMap.txt");
    gamewindow.start(lvl);
    lvl.close();
    gamewindow.getGame().setisGame(true);
    gamewindow.drawGame();
    gamewindow.setSize();
    gamewindow.startTick();
    gamewindow.showFullScreen();
    emit closeWindow();
}

void Title::continueGame(){
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/Maps/Saved1.txt");
    gamewindow.start(lvl);
    lvl.close();
    gamewindow.getGame().setisGame(true);
    gamewindow.drawGame();
    gamewindow.setSize();
    gamewindow.startTick();
    gamewindow.showFullScreen();
    emit closeWindow();
}

void Title::quitGame(){
    qApp->quit();
}

