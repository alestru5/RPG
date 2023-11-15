#include "gamewindow.h"
#include "cell.h"
#include "character.h"
#include "hero.h"

void GameWindow::setSize(){
    this->setFixedSize(1920,1080);
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
    shadowPix.load("/home/alestru/PetProjects/RPG/img/black.png");
    chestPix.load("/home/alestru/PetProjects/RPG/img/chest.png");
    ladderPix.load("/home/alestru/PetProjects/RPG/img/ladder.png");
    openDoorPix.load("/home/alestru/PetProjects/RPG/img/open_door.png");
    closeDoorPix.load("/home/alestru/PetProjects/RPG/img/close_door.png");


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



    info = new QLabel(this);
    info->setGeometry(0, 0, 1920, infoHeight);
    info->setStyleSheet("background-color: #000000; border-bottom: 10 px white;");

    statusLabel = new QLabel(this);
    statusLabel->setGeometry(70, 10, 1920 - 50 - 20, 50);
    statusLabel->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 8pt;font-weight: bold; background-color: #000000; border-bottom: 10 px white;");

    QPixmap avatar;
    avatar.load("/home/alestru/PetProjects/RPG/img/player_avatar.png");
    QLabel *avatarLabel = new QLabel(this);
    avatarLabel->setGeometry(10, 10, 50, 50);
    avatarLabel->setPixmap(avatar.scaledToHeight(50));

    game.initGame();

    inventorySlot.assign(2, std::vector<QLabel*>(5));
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            inventorySlot[i][j] = new QLabel(this);
            inventorySlot[i][j]->setGeometry((game.getMapWidth() - 1) * tileHeight  - j * tileHeight - j * tileHeight / 16, i * tileHeight + i * tileHeight/16, tileHeight * 31 / 32, tileHeight * 31 / 32);
            inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
            if (game.getDungeon().getHero().getCurr_Chosen_Item() == 5 * (i + 1) - j - 1){
                inventorySlot[i][j]->setStyleSheet("border: 3px dashed red;");
            }
        }
    }

    equipmentSlot.assign(2, std::vector<QLabel*>(2));
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            equipmentSlot[i][j] = new QLabel(this);
            equipmentSlot[i][j]->setGeometry((game.getMapWidth() - 1) * tileHeight  - j * tileHeight - j * tileHeight / 16 - tileHeight * 6 - tileHeight / 4, i * tileHeight + i * tileHeight/16, tileHeight * 31 / 32, tileHeight * 31 / 32);
            equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
        }
    }

    weaponSlot = new QLabel(this);
    weaponSlot->setGeometry((game.getMapWidth() - 1) * tileHeight  - 9 * tileHeight - 5 * tileHeight / 16, 0, tileHeight * 31 / 32, tileHeight * 31 / 32);
    weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed white;");

    statusLabel->setText(QString::fromStdString(status()));

    tile.assign(game.getMapHeight(), std::vector<QLabel*>(game.getMapWidth()));
    hpTile.assign(game.getMapHeight(), std::vector<QLabel*>(game.getMapWidth()));

    for (int i = 0; i < game.getMapHeight(); i++){
        for (int j = 0; j < game.getMapWidth(); j++){
            tile[i][j] = new QLabel(this);
            tile[i][j]->setGeometry(j * tileHeight,infoHeight + i * tileHeight, tileHeight, tileHeight);
            tile[i][j]->setStyleSheet("background-color: #3D3D3D;");

            hpTile[i][j] = new QLabel(this);
            hpTile[i][j]->setGeometry(j * tileHeight, infoHeight + i * tileHeight, tileHeight, tileHeight);
            hpTile[i][j]->setAlignment(Qt::AlignCenter);
            hpTile[i][j]->setStyleSheet("color: white; font-size: 12pt; font-weight: bold; ");
        }
    }
    drawGame();

    timer = startTimer(1000);
}

void GameWindow::mousePressEvent(QMouseEvent *e){
    if (e->button() == Qt::LeftButton){
        act("left");
    }
    else if (e->button() == Qt::RightButton){
        act("right");
    }
    drawGame();


}
void GameWindow::keyPressEvent(QKeyEvent* e){
    std::string key = e->text().toLocal8Bit().constData();
    if (key == "w" || key == "a" || key == "s" || key == "d" || key == "e" || key == "f" || key == "t" || key == "u" || key == "i" ||  key == "o" || key == "p"
        || key == " "){
        act(key);
    }else{
        return;
    }

    if (game.getDungeon().getCurLevel()[game.getDungeon().getHero().getX()][game.getDungeon().getHero().getY()].getType() == type_cell::open_door){
        playerPix[0].load("/home/alestru/PetProjects/RPG/img/H_open_door.png");
    } else if (game.getDungeon().getCurLevel()[game.getDungeon().getHero().getX()][game.getDungeon().getHero().getY()].isLadder()){
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
    if (game.tick(game.getDungeon())){
        drawGame();
    }
    else{

    }

}

void GameWindow::drawGame(){
    statusLabel->setText(QString::fromStdString(status()));

    if (game.getDungeon().getHero().getWeapon() != nullptr
        && (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon ||
        game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact ||
        game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact_enchantment ||
            game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_enchantment)){
        if (game.getDungeon().getHero().getWeapon()->getWeapon_Name() == name_weapon::knife){
            weaponSlot->setPixmap(itemsPix["knife"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
        }
        else if (game.getDungeon().getHero().getWeapon()->getWeapon_Name() == name_weapon::nunchucks){
            weaponSlot->setPixmap(itemsPix["nunchucks"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
        }
        else if (game.getDungeon().getHero().getWeapon()->getWeapon_Name() == name_weapon::sword){
            weaponSlot->setPixmap(itemsPix["sword"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
        }

        if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact){
            if (dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::rare){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed blue;");
            } else if (dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::mythical){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed purple;");
            } else if (dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::legendary){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed yellow;");
            } else if (dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::casual){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed white;");
            }
        } else if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact_enchantment){
            if (dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::rare){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed blue;");
            } else if (dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::mythical){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed purple;");
            } else if (dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::legendary){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed yellow;");
            } else if (dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type() == type_artifact::casual){
                weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed white;");
            }
        } else {
            weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed white;");
        }
    }

    std::list<Equipment *> T = game.getDungeon().getHero().getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        int i;
        int j;
        if ((*iter)->getEquipment_Type() == type_equipment::bib){
            equipmentSlot[0][0]->setPixmap(itemsPix["bib"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
            i = 0;
            j = 0;
        } else if ((*iter)->getEquipment_Type() == type_equipment::boots){
            equipmentSlot[1][0]->setPixmap(itemsPix["boots"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
            i = 1;
            j = 0;
        } else if ((*iter)->getEquipment_Type() == type_equipment::helmet){
            equipmentSlot[0][1]->setPixmap(itemsPix["helmet"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
            i = 0;
            j = 1;
        } else if ((*iter)->getEquipment_Type() == type_equipment::leggings){
            equipmentSlot[1][1]->setPixmap(itemsPix["leggings"].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
            i = 1;
            j = 1;
        }

        if ((*iter)->getItem_Type() == type_item::equipment_artifact){
            if (static_cast<EquipmentArtifact *>(*iter)->getArtifact_Type() == type_artifact::casual){
                equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
            } else if (static_cast<EquipmentArtifact *>(*iter)->getArtifact_Type() == type_artifact::rare){
                equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed blue;");
            } else if (static_cast<EquipmentArtifact *>(*iter)->getArtifact_Type() == type_artifact::mythical){
                equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed purple;");
            } else if (static_cast<EquipmentArtifact *>(*iter)->getArtifact_Type() == type_artifact::legendary){
                equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed yellow;");
            }
        } else {
            equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
        }
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
            if (game.getDungeon().getHero().getCurr_Chosen_Item() == 5 * (i + 1) - j - 1){
                inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed red;");
            }
            if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1] == nullptr) {
                inventorySlot[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
                continue;
            }
            if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::bunch){
                inventorySlot[i][j]->setPixmap(itemsPix["bunch"].scaledToHeight(tileHeight));
            }
            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::equipment ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::equipment_artifact){
                if (static_cast<Equipment*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getEquipment_Type() == type_equipment::helmet){
                    inventorySlot[i][j]->setPixmap(itemsPix["helmet"].scaledToHeight(tileHeight));
                }
                else if (static_cast<Equipment*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getEquipment_Type() == type_equipment::bib){
                    inventorySlot[i][j]->setPixmap(itemsPix["bib"].scaledToHeight(tileHeight));
                }
                else if (static_cast<Equipment*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getEquipment_Type() == type_equipment::leggings){
                    inventorySlot[i][j]->setPixmap(itemsPix["leggings"].scaledToHeight(tileHeight));
                }
                else if (static_cast<Equipment*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getEquipment_Type() == type_equipment::boots){
                    inventorySlot[i][j]->setPixmap(itemsPix["boots"].scaledToHeight(tileHeight));
                }
            }
            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::potion){
                inventorySlot[i][j]->setPixmap(itemsPix["potion"].scaledToHeight(tileHeight));
            }
            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact_enchantment ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_enchantment){
                if (static_cast<Weapon*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getWeapon_Name() == name_weapon::knife){
                    inventorySlot[i][j]->setPixmap(itemsPix["knife"].scaledToHeight(tileHeight));
                }
                else if (static_cast<Weapon*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getWeapon_Name() == name_weapon::nunchucks){
                    inventorySlot[i][j]->setPixmap(itemsPix["nunchucks"].scaledToHeight(tileHeight));
                }
                else if (static_cast<Weapon*>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getWeapon_Name() == name_weapon::sword){
                    inventorySlot[i][j]->setPixmap(itemsPix["sword"].scaledToHeight(tileHeight));
                }
            }
        }
    }

    for (int i = 0; i < game.getMapHeight(); i++){
        for (int j = 0; j < game.getMapWidth(); j++){
            if (std::pow(game.getDungeon().getHero().getX() - i, 2) + std::pow(game.getDungeon().getHero().getY() - j, 2) > 36){
                tile[i][j]->setPixmap(shadowPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
                continue;
            }
            if (i == game.getDungeon().getHero().getX() && j == game.getDungeon().getHero().getY()){
                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (game.getDungeon().getCurLevel()[i][j].getType() == type_cell::wall){
                tile[i][j]->setPixmap(wallPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (game.getDungeon().getCurLevel()[i][j].getType() == type_cell::floor && game.getDungeon().getLevels()[game.getDungeon().getCur_Level()][i][j].getChest() != nullptr){
                tile[i][j]->setPixmap(chestPix.scaledToHeight(tileHeight));
            }
            else if (game.getDungeon().getCurLevel()[i][j].getItem()){
                if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::bunch){
                    tile[i][j]->setPixmap(itemsPix["bunch"].scaledToHeight(tileHeight));
                    hpTile[i][j]->setText("");
                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment_artifact){
                    if (static_cast<Equipment*>(game.getDungeon().getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::helmet){
                        tile[i][j]->setPixmap(itemsPix["helmet"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(game.getDungeon().getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::bib){
                        tile[i][j]->setPixmap(itemsPix["bib"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(game.getDungeon().getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::leggings){
                        tile[i][j]->setPixmap(itemsPix["leggings"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Equipment*>(game.getDungeon().getCurLevel()[i][j].getItem())->getEquipment_Type() == type_equipment::boots){
                        tile[i][j]->setPixmap(itemsPix["boots"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                }
                else if (game.getDungeon().getLevels()[game.getDungeon().getCur_Level()][i][j].getItem()->getItem_Type() == type_item::potion){
                    tile[i][j]->setPixmap(itemsPix["potion"].scaledToHeight(tileHeight));
                    hpTile[i][j]->setText("");
                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact_enchantment ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_enchantment){
                    if (static_cast<Weapon*>(game.getDungeon().getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::knife){
                        tile[i][j]->setPixmap(itemsPix["knife"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Weapon*>(game.getDungeon().getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::nunchucks){
                        tile[i][j]->setPixmap(itemsPix["nunchucks"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                    else if (static_cast<Weapon*>(game.getDungeon().getCurLevel()[i][j].getItem())->getWeapon_Name() == name_weapon::sword){
                        tile[i][j]->setPixmap(itemsPix["sword"].scaledToHeight(tileHeight));
                        hpTile[i][j]->setText("");
                    }
                }
            }
            else if (game.getDungeon().getCurLevel()[i][j].getType() == type_cell::down_ladder ||
                     game.getDungeon().getCurLevel()[i][j].getType() == type_cell::up_ladder){
                tile[i][j]->setPixmap(ladderPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (game.getDungeon().getCurLevel()[i][j].getType() == type_cell::open_door){
                tile[i][j]->setPixmap(openDoorPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else if (game.getDungeon().getCurLevel()[i][j].getType() == type_cell::close_door){
                tile[i][j]->setPixmap(closeDoorPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
            else{
                tile[i][j]->setPixmap(nothingPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
            }
        }
    }
    for (size_t i = 0; i < game.getDungeon().getEnemies().size(); i++){
        if (std::pow(game.getDungeon().getHero().getX() - game.getDungeon().getEnemies()[i].second->getX(), 2) + std::pow(game.getDungeon().getHero().getY() - game.getDungeon().getEnemies()[i].second->getY(), 2) > 36){
            tile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setPixmap(shadowPix.scaledToHeight(tileHeight));
            hpTile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setText("");
            continue;
        }
        if (game.getDungeon().getEnemies()[i].first == game.getDungeon().getCur_Level() && game.getDungeon().getEnemies()[i].second->getName() == name_enemy::black_druid){
            tile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setPixmap(mobPix["druid"].scaledToHeight(tileHeight));

        } else if (game.getDungeon().getEnemies()[i].first == game.getDungeon().getCur_Level() && game.getDungeon().getEnemies()[i].second->getName() == name_enemy::blue_wolf){
            tile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setPixmap(mobPix["wolf"].scaledToHeight(tileHeight));    
        }
        else if (game.getDungeon().getEnemies()[i].first == game.getDungeon().getCur_Level() && game.getDungeon().getEnemies()[i].second->getName() == name_enemy::red_tiger){
            tile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setPixmap(mobPix["tiger"].scaledToHeight(tileHeight));
        }
        else if (game.getDungeon().getEnemies()[i].first == game.getDungeon().getCur_Level() && game.getDungeon().getEnemies()[i].second->getName() == name_enemy::white_golem){
            tile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setPixmap(mobPix["golem"].scaledToHeight(tileHeight));
        }
        if (game.getDungeon().getEnemies()[i].first == game.getDungeon().getCur_Level()){
            if (!game.getDungeon().getEnemies()[i].second->isDead()){
                hpTile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setText(QString::number(game.getDungeon().getEnemies()[i].second->getCur_Hp()));
            } else{
                hpTile[game.getDungeon().getEnemies()[i].second->getX()][game.getDungeon().getEnemies()[i].second->getY()]->setText("DEAD");
            }
        }
    }
}

void GameWindow::act(std::string key){
    std::string command = "invalid";
    if (key == "w") command = "north";
    else if (key == "s") command = "south";
    else if (key == "d") command = "east";
    else if (key == "a") command = "west";
    else if (key == "e") command = "action";
    else if (key == "right") command = "change";
    else if (key == "left") command = "attack";
    else if (key == "t") command = "drink";
    else if (key == "u") command = "strength";
    else if (key == "i") command = "intelligence";
    else if (key == "o") command = "agility";
    else if (key == "p") command = "endurance";
    else if (key == " ") command = "use";
    if (command == "south" || command == "east" || command == "west" || command == "north"){
        type_destination destination;
        if (command == "south"){
            destination = type_destination::south;
        } else if (command == "east"){
            destination = type_destination::east;
        } else if (command == "west"){
            destination = type_destination::west;
        } else if (command == "north"){
            destination = type_destination::north;
        }
        game.getDungeon().getHero().move(destination, game.getDungeon());
    } else if (command == "action"){
        if (game.getDungeon().getHero().climb(game.getDungeon())){
            return;
        }
        if (game.getDungeon().getHero().open_chest(game.getDungeon())){
            return;
        }
        if (game.getDungeon().getHero().take(game.getDungeon())){
            game.getDungeon().getHero().updateHp();
            return;
        }
        if (game.getDungeon().getHero().change_door(game.getDungeon())){
            return;
        }
        return;
    } else if (command == "attack"){
        int ind_enemy = game.getDungeon().getHero().findEnemy(game.getDungeon());
        if (ind_enemy != -1){
            game.getDungeon().getHero().attack(game.getDungeon().getEnemies()[ind_enemy].second);
            if (game.getDungeon().getEnemies()[ind_enemy].second->isDead()){
                game.getDungeon().getHero().addExperience(game.getDungeon().getEnemies()[ind_enemy].second->getExperience());
                game.getDungeon().getEnemies()[ind_enemy].second->dropItem(game.getDungeon());
                game.getDungeon().enemyDead(ind_enemy);
            }
        }
    } else if (command == "change"){
        game.getDungeon().getHero().nextChosenItem();

    } else if (command == "strength" || command == "intelligence" || command == "agility" || command == "endurance"){
        short_characteristic up;
        if (command == "strength") up = short_characteristic::s;
        if (command == "intelligence") up = short_characteristic::i;
        if (command == "agility") up = short_characteristic::a;
        if (command == "endurance") up = short_characteristic::e;
        game.getDungeon().getHero().levelUp(up);
    } else if (command == "use"){
        game.getDungeon().getHero().usingChosenItem(game.getDungeon());
    }
    game.getDungeon().getHero().updateHp();
}

std::string GameWindow::status(){
    std::string res;
    res += "HP: " + std::to_string(game.getDungeon().getHero().getCur_Hp()) + "/" + std::to_string(game.getDungeon().getHero().getMax_Hp());
    res += "\t\t\t\tDungeon Level: " + std::to_string(-game.getDungeon().getCur_Level());
    res += "\t\t\t\tProtect: " + std::to_string(game.getDungeon().getHero().minProtect()) + "-" + std::to_string(game.getDungeon().getHero().maxProtect()) + "(+" + std::to_string(game.getDungeon().getHero().getTable().getValue(full_characteristic::strength) / 10) + ")";
    res += "\t\t\t\tFull damage: " + std::to_string(game.getDungeon().getHero().minDamage()) + "-" + std::to_string(game.getDungeon().getHero().maxDamage()) + "(+" + std::to_string(game.getDungeon().getHero().getTable().getValue(full_characteristic::agility    ) / 10) + ")";
    res += "\nWeapon: ";
    if (game.getDungeon().getHero().getWeapon() != nullptr){
        if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact){
            res += EnumToString::toString(dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type()) + " ";
        }
        if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_enchantment){
            res += EnumToString::toString(dynamic_cast<WeaponEnchantment *>(game.getDungeon().getHero().getWeapon())->getEnchantment_Type()) + " ";
        }
        if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact_enchantment){
            res += EnumToString::toString(dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type()) + " ";
            res += EnumToString::toString(dynamic_cast<WeaponArtifactEnchantment *>(game.getDungeon().getHero().getWeapon())->getEnchantment_Type()) + " ";
        }
        res += EnumToString::toString(game.getDungeon().getHero().getWeapon()->getWeapon_Name());
    } else{
        res += "None";
    }
    res += "\tStrength: " + std::to_string(game.getDungeon().getHero().getTable().getValue(short_characteristic::s));
    res += "\tAgility: " + std::to_string(game.getDungeon().getHero().getTable().getValue(short_characteristic::a));
    res += "\tIntelligence: " + std::to_string(game.getDungeon().getHero().getTable().getValue(short_characteristic::i));
    res += "\tExperience: " + std::to_string(game.getDungeon().getHero().getExperience());
    res += "\tEndurance: " + std::to_string(game.getDungeon().getHero().getCur_Endurance()) + "/" + std::to_string(game.getDungeon().getHero().getTable().getValue(short_characteristic::e));
    res += "\nHelmet: ";
    int f = 1;
    std::list<Equipment*> E = game.getDungeon().getHero().getEquipment();
    for (auto iter = E.begin(); iter !=  E.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::helmet){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Bib: ";
    f = 1;
    for (auto iter =  E.begin(); iter !=  E.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::bib){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Leggings: ";
    f = 1;
    for (auto iter =  E.begin(); iter !=  E.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::leggings){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Boots: ";
    f = 1;
    for (auto iter =  E.begin(); iter !=  E.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::boots){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "\nBunch: " + std::to_string(game.getDungeon().getHero().getC_Bunch());
    return res;
}

