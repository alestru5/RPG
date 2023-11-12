#include "gamewindow.h"
#include "cell.h"
#include "character.h"
#include "game.h"

void GameWindow::setSize(){
    this->setFixedSize(1280,720);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

GameWindow::GameWindow(QMainWindow *parent): QMainWindow(parent){
    setWindowTitle("Vagabund");
    playerPix.resize(1);

    wallPix.load("/home/alestru/PetProjects/RPG/img/wall.png");
    playerPix[0].load("/home/alestru/PetProjects/RPG/img/player1.png");
    nothingPix.load("/home/alestru/PetProjects/RPG/img/nothing.png");
    chestPix.load("/home/alestru/PetProjects/RPG/img/chest.png");
    ladderPix.load("/home/alestru/PetProjects/RPG/img/ladder.png");
    openDoorPix.load("/home/alestru/PetProjects/RPG/img/open_door.png");
    closeDoorPix.load("/home/alestru/PetProjects/RPG/img/close_door.png");

    QPixmap avatar;
    avatar.load("/home/alestru/PetProjects/RPG/img/player_avatar.png");
    QLabel *avatarLabel = new QLabel(this);
    avatarLabel->setGeometry(10, 10, 50, 50);
    avatarLabel->setPixmap(avatar.scaledToHeight(50));

    itemsPix["knife"].load("/home/alestru/PetProjects/RPG/img/knife.png");
    itemsPix["sword"].load("/home/alestru/PetProjects/RPG/img/sword.png");
    itemsPix["nunchucks"].load("/home/alestru/PetProjects/RPG/img/nunchucks.png");
    itemsPix["helmet"].load("/home/alestru/PetProjects/RPG/img/helmet.png");
    itemsPix["bib"].load("/home/alestru/PetProjects/RPG/img/bib.png");
    itemsPix["leggings"].load("/home/alestru/PetProjects/RPG/img/leggings.png");
    itemsPix["boots"].load("/home/alestru/PetProjects/RPG/img/boots.png");
    itemsPix["bunch"].load("/home/alestru/PetProjects/RPG/img/bunch.png");
    itemsPix["potion"].load("/home/alestru/PetProjects/RPG/img/potion.png");

    mobPix["golem"].load("/home/alestru/PetProjects/RPG/img/golem_npc.png");
    mobPix["druid"].load("/home/alestru/PetProjects/RPG/img/druid_npc.png");
    mobPix["tiger"].load("/home/alestru/PetProjects/RPG/img/tiger_npc.png");
    mobPix["wolf"].load("/home/alestru/PetProjects/RPG/img/wolf_npc.png");

    statusLabel = new QLabel(this);
    statusLabel->setGeometry(70, 10, 1920 - 50 - 20, 50);
    statusLabel->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 8pt;font-weight: bold;");

    Game::initGame();

    statusLabel->setText(QString::fromStdString(Game::dungeon.getHero().status()));

    tile.assign(Game::mapHeight, std::vector<QLabel*>(Game::mapWidth));
    hpTile.assign(Game::mapHeight, std::vector<QLabel*>(Game::mapWidth));

    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            tile[i][j] = new QLabel(this);
            tile[i][j]->setGeometry(j * tileHeight,infoHeight + i * tileHeight, tileHeight, tileHeight);

            hpTile[i][j] = new QLabel(this);
            hpTile[i][j]->setGeometry(j * tileHeight, infoHeight + i * tileHeight, tileHeight, tileHeight);
            hpTile[i][j]->setAlignment(Qt::AlignCenter);
            hpTile[i][j]->setStyleSheet("color: white; font-size: 12pt; font-weight: bold;");
        }
    }
    drawGame();

    this->setStyleSheet("QMainWindow {background-color: black;}");
    timer = startTimer(2000);
}

void GameWindow::keyPressEvent(QKeyEvent* e){
    std::string key = e->text().toLocal8Bit().constData();
    if (key == "w" || key == "a" || key == "s" || key == "d" || key == "e" || key == "f"){
        Game::dungeon.getHero().act(key);
    }else{
        return;
    }
    statusLabel->setText(QString::fromStdString(Game::dungeon.getHero().status()));

    if (Game::dungeon.getCurLevel()[Game::dungeon.getHero().getX()][Game::dungeon.getHero().getY()].getType() == type_cell::open_door){
        playerPix[0].load("/home/alestru/PetProjects/RPG/img/H_open_door.png");
    } else if (Game::dungeon.getCurLevel()[Game::dungeon.getHero().getX()][Game::dungeon.getHero().getY()].isLadder()){
        playerPix[0].load("/home/alestru/PetProjects/RPG/img/H_ladder.png");
    } else{
        if (key == "a"){
            playerPix[0].load("/home/alestru/PetProjects/RPG/img/player_left.png");
        } else{
            playerPix[0].load("/home/alestru/PetProjects/RPG/img/player_right.png");
        }
    }
    drawGame();
}

void GameWindow::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    if (Game::tick()){
        drawGame();
    }
    else{
        QMessageBox msgb;
        msgb.setText("Game Over");
        msgb.exec();
    }

}

void GameWindow::drawGame(){
    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            if (std::pow(Game::dungeon.getHero().getX() - i, 2) + std::pow(Game::dungeon.getHero().getY() - j, 2) > 36){
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
                continue;
            }
            if (i == Game::dungeon.getHero().getX() && j == Game::dungeon.getHero().getY()){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::wall){
                tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::floor && Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getChest() != nullptr){
                tile[i][j]->setPixmap(chestPix.scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getItem()){
                if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::bunch){
                    tile[i][j]->setPixmap(itemsPix["bunch"].scaledToHeight(tileHeight));
                    hpTile[i][j]->setText("");
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment_artifact){
                    if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::helmet){
                        tile[i][j]->setPixmap(itemsPix["helmet"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::bib){
                        tile[i][j]->setPixmap(itemsPix["bib"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::leggings){
                        tile[i][j]->setPixmap(itemsPix["leggings"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::boots){
                        tile[i][j]->setPixmap(itemsPix["boots"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                }
                else if (Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getItem()->getItem_Type() == type_item::potion){
                    tile[i][j]->setPixmap(itemsPix["potion"].scaledToHeight(tileHeight));
                    hpTile[i][j]->setText("");
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact_enchantment ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_enchantment){
                    if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::knife){
                        tile[i][j]->setPixmap(itemsPix["knife"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::nunchucks){
                        tile[i][j]->setPixmap(itemsPix["nunchucks"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::sword){
                        tile[i][j]->setPixmap(itemsPix["sword"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                }
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::down_ladder ||
                     Game::dungeon.getCurLevel()[i][j].getType() == type_cell::up_ladder){
                tile[i][j]->setPixmap(ladderPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::open_door){
                tile[i][j]->setPixmap(openDoorPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::close_door){
                tile[i][j]->setPixmap(closeDoorPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else{
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
        }
    }
    for (size_t i = 0; i < Game::dungeon.getEnemies().size(); i++){
        if (std::pow(Game::dungeon.getHero().getX() - Game::dungeon.getEnemies()[i].second->getX(), 2) + std::pow(Game::dungeon.getHero().getY() - Game::dungeon.getEnemies()[i].second->getY(), 2) > 36){
            tile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setPixmap(nothingPix.scaledToHeight(tileHeight));
            hpTile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setText("");
            continue;
        }
        if (Game::dungeon.getEnemies()[i].first == Game::dungeon.getCur_Level() && Game::dungeon.getEnemies()[i].second->getName() == name_enemy::black_druid){
            tile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setPixmap(mobPix["druid"].scaledToHeight(tileHeight));
            hpTile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setText(QString::number(Game::dungeon.getEnemies()[i].second->getCur_Hp()));
        } else if (Game::dungeon.getEnemies()[i].first == Game::dungeon.getCur_Level() && Game::dungeon.getEnemies()[i].second->getName() == name_enemy::blue_wolf){
            tile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setPixmap(mobPix["wolf"].scaledToHeight(tileHeight));
            hpTile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setText(QString::number(Game::dungeon.getEnemies()[i].second->getCur_Hp()));
        }
        else if (Game::dungeon.getEnemies()[i].first == Game::dungeon.getCur_Level() && Game::dungeon.getEnemies()[i].second->getName() == name_enemy::red_tiger){
            tile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setPixmap(mobPix["tiger"].scaledToHeight(tileHeight));
            hpTile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setText(QString::number(Game::dungeon.getEnemies()[i].second->getCur_Hp()));
        }
        else if (Game::dungeon.getEnemies()[i].first == Game::dungeon.getCur_Level() && Game::dungeon.getEnemies()[i].second->getName() == name_enemy::white_golem){
            tile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setPixmap(mobPix["golem"].scaledToHeight(tileHeight));
            hpTile[Game::dungeon.getEnemies()[i].second->getX()][Game::dungeon.getEnemies()[i].second->getY()]->setText(QString::number(Game::dungeon.getEnemies()[i].second->getCur_Hp()));
        }

    }
}


