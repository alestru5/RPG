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
    chestPix.load("/home/alestru/PetProjects/RPG/img/chest.png");
    ladderPix.load("/home/alestru/PetProjects/RPG/img/ladder.png");

    Game::mapWidth = 32;
    Game::mapHeight = 16;

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


    statusLabel = new QLabel(this);
    statusLabel->setGeometry(70, 10, 1920 - 50 - 20, 50);
    statusLabel->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 8pt;font-weight: bold;");
    statusLabel->setText(QString::fromStdString(Game::dungeon.getHero().status()));

    tile.assign(100, std::vector<QLabel*>(200));
    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            tile[i][j] = new QLabel(this);
            tile[i][j]->setGeometry(j * tileHeight,infoHeight + i * tileHeight, tileHeight, tileHeight);
            if (i == Game::dungeon.getHero().getX() && j == Game::dungeon.getHero().getY()){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::wall){
                tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::floor && Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getChest() != nullptr){
                tile[i][j]->setPixmap(chestPix.scaledToHeight(tileHeight));  
            }
            else if (Game::dungeon.getCurLevel()[i][j].getItem()){
                if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::bunch){
                    tile[i][j]->setPixmap(itemsPix["bunch"].scaledToHeight(tileHeight));
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment_artifact){
                    if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::helmet){
                        tile[i][j]->setPixmap(itemsPix["helmet"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::bib){
                        tile[i][j]->setPixmap(itemsPix["bib"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::leggings){
                        tile[i][j]->setPixmap(itemsPix["leggings"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::boots){
                        tile[i][j]->setPixmap(itemsPix["boots"].scaledToHeight(tileHeight));
                    }
                }
                else if (Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getItem()->getItem_Type() == type_item::potion){
                    tile[i][j]->setPixmap(itemsPix["potion"].scaledToHeight(tileHeight));
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon ||
                           Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact ||
                           Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact_enchantment ||
                           Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_enchantment){
                    if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::knife){
                        tile[i][j]->setPixmap(itemsPix["knife"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::nunchucks){
                        tile[i][j]->setPixmap(itemsPix["nunchucks"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::sword){
                        tile[i][j]->setPixmap(itemsPix["sword"].scaledToHeight(tileHeight));
                    }
                }
            }
            else if (Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getType() == type_cell::down_ladder ||
                       Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getType() == type_cell::up_ladder){
                tile[i][j]->setPixmap(ladderPix.scaledToHeight(tileHeight));
            }
            else{
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
            }
        }
    }
    this->setStyleSheet("QMainWindow {background-color: black;}");
}

void GameWindow::keyPressEvent(QKeyEvent* e){
    std::string key = e->text().toLocal8Bit().constData();
    if (key == "w" || key == "a" || key == "s" || key == "d" || key == "e" || key == "f"){
        if (key == "a"){
            playerPix[0].load("/home/alestru/PetProjects/RPG/img/player_left.png");
        }
        if (key == "d"){
            playerPix[0].load("/home/alestru/PetProjects/RPG/img/player_right.png");
        }
        Game::dungeon.getHero().act(key);
    }else{
        return;
    }

    statusLabel->setText(QString::fromStdString(Game::dungeon.getHero().status()));

    for (int i = 0; i < Game::mapHeight; i++){
        for (int j = 0; j < Game::mapWidth; j++){
            if (i == Game::dungeon.getHero().getX() && j == Game::dungeon.getHero().getY()){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::wall){
                tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getType() == type_cell::floor && Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getChest() != nullptr){
                tile[i][j]->setPixmap(chestPix.scaledToHeight(tileHeight));
            }
            else if (Game::dungeon.getCurLevel()[i][j].getItem()){
                if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::bunch){
                    tile[i][j]->setPixmap(itemsPix["bunch"].scaledToHeight(tileHeight));
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment_artifact){
                    if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::helmet){
                        tile[i][j]->setPixmap(itemsPix["helmet"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::bib){
                        tile[i][j]->setPixmap(itemsPix["bib"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::leggings){
                        tile[i][j]->setPixmap(itemsPix["leggings"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Equipment*>(Game::dungeon.getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::boots){
                        tile[i][j]->setPixmap(itemsPix["boots"].scaledToHeight(tileHeight));
                    }
                }
                else if (Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getItem()->getItem_Type() == type_item::potion){
                    tile[i][j]->setPixmap(itemsPix["potion"].scaledToHeight(tileHeight));
                }
                else if (Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact_enchantment ||
                         Game::dungeon.getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_enchantment){
                    if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::knife){
                        tile[i][j]->setPixmap(itemsPix["knife"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::nunchucks){
                        tile[i][j]->setPixmap(itemsPix["nunchucks"].scaledToHeight(tileHeight));
                    }
                    else if (static_cast<Weapon*>(Game::dungeon.getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::sword){
                        tile[i][j]->setPixmap(itemsPix["sword"].scaledToHeight(tileHeight));
                    }
                }
            }
            else if (Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getType() == type_cell::down_ladder ||
                     Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][i][j].getType() == type_cell::up_ladder){
                tile[i][j]->setPixmap(ladderPix.scaledToHeight(tileHeight));
            }
            else{
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

