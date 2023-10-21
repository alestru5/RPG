#include "gamewindow.h"
#include "cell.h"
#include "character.h"
#include "game.h"
GameWindow::GameWindow(QMainWindow *parent): QMainWindow(parent){
    setWindowTitle("Vagabund");
    playerPix.resize(1);

    wallPix.load("/home/alestru/PetProjects/RPG/img/wall.png");
    playerPix[0].load("/home/alestru/PetProjects/RPG/img/player1.png");
    nothingPix.load("/home/alestru/PetProjects/RPG/img/nothing.png");

    Game::mapWidth = 32;
    Game::mapHeight = 16;

    tile.assign(100, std::vector<QLabel*>(200));
    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            tile[i][j] = new QLabel(this);
            tile[i][j]->setGeometry(j * tileHeight,infoHeight + i * tileHeight, tileHeight, tileHeight);
            if (Game::dungeon.getLevels()[0][i][j].getType() == type_cell::hero){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
                Game::hero = Hero(i, j);
            }
            else if (Game::dungeon.getLevels()[0][i][j].getType() == type_cell::wall){
                tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
            }
            else
            {
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
            }
        }
    }
    this->setStyleSheet("QMainWindow {background-color: black;}");
}

void GameWindow::keyPressEvent(QKeyEvent* e){
    std::string key = e->text().toLocal8Bit().constData();
    if (key == "w" || key == "a" || key == "s" || key == "d"){
        Game::hero.act(key);
    }else{
        return;
    }

    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            if (Game::dungeon.getLevels()[0][i][j].getType() == type_cell::hero){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getLevels()[0][i][j].getType() == type_cell::floor){
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
            }
        }
    }
}

void GameWindow::setSize(){
    this->setFixedSize(1280,720);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

