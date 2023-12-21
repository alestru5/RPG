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
    connect(continueButton, SIGNAL(clicked()), this, SLOT(changesButton()));

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
    lvl.open("/home/alestru/PetProjects/RPG/Maps/NewMap.txt");
    config.open("/home/alestru/PetProjects/RPG/config.json");

    gamewindow.start(lvl, nlohmann::json::parse(config), pluginsDir);
    gamewindow.getGame().setisGame(true);
    gamewindow.drawGame();
    gamewindow.setSize();
    gamewindow.startTick();
    gamewindow.showFullScreen();


    emit closeWindow();
}

void Title::startSelectGame(std::string pathMap){
    lvl.open(pathMap);
    config.open("/home/alestru/PetProjects/RPG/config.json");

    gamewindow.start(lvl, nlohmann::json::parse(config), pluginsDir);
    gamewindow.getGame().setisGame(true);
    gamewindow.drawGame();
    gamewindow.setSize();
    gamewindow.startTick();
    gamewindow.showFullScreen();

    lvl.close();
    config.close();
    emit closeWindow();
}

void Title::changesButton(){
    QString path = "/home/alestru/PetProjects/RPG/Maps";
    QDir directory(path);
    if (!directory.exists()) {
        return;
    }
    startButton->setVisible(false);
    continueButton->setVisible(false);
    quitButton->setVisible(false);
    QStringList list = directory.entryList(QDir::Files);
    count = 0;
    for (int i = 0; i < list.size(); ++i) {
        QString fileInfo = list.at(i);

        if (fileInfo.toStdString().find("Saved") != std::string::npos && fileInfo.toStdString().find(".txt") != std::string::npos){
            count += 1;
        }
    }
    int t = 0;
    mapsButton = new QPushButton*[count];
    for (int i = 0; i < list.size(); ++i) {
        QString filename = list.at(i);
        std::string filePath = (path + "/").toStdString() + filename.toStdString();
        if (filename.toStdString().find("Saved") != std::string::npos && filename.toStdString().find(".txt") != std::string::npos){
            QString text = filename.split(".")[0];

            mapsButton[t] = new QPushButton(viewer);
            mapsButton[t]->setText(text);
            mapsButton[t]->setObjectName(text);
            mapsButton[t]->setGeometry(QRect(width/2 - 150, height / 2 - count / 2 * 50 + 60 * t, 300, 50));
            mapsButton[t]->setVisible(true);
            connect(mapsButton[t], &QPushButton::clicked, this, [=]() {
                startSelectGame(filePath);
            });
            t += 1;
        }
    }
    backButton = new QPushButton(viewer);
    backButton->setText("Back");
    backButton->setObjectName(QString("backButton"));
    backButton->setToolTip("Back to menu");
    backButton->setGeometry(QRect(width/2 - 150, height / 2 - count / 2 * 50 + 60 * t, 300, 50));
    backButton->setVisible(true);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backToMenu()));

}

void Title::backToMenu(){
    for (int i = 0; i < count; i++){
        mapsButton[i]->setVisible(false);
    }
    backButton->setVisible(false);
    startButton->setVisible(true);
    continueButton->setVisible(true);
    quitButton->setVisible(true);
}


void Title::quitGame(){
    qApp->quit();
}

