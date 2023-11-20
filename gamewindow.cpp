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

    loadImg();

    info = new QLabel(this);
    info->setGeometry(0, 0, 1920, infoHeight);
    info->setStyleSheet("background-color: #000000; border-bottom: 10 px white;");

    statusLabel = new QLabel(this);
    statusLabel->setGeometry(70, 10, 1920 - 50 - 20, 50);
    statusLabel->setStyleSheet("color: white; font-family: Arial;font-style: normal;font-size: 8pt;font-weight: bold; background-color: #000000; border-bottom: 10 px white;");

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

void GameWindow::loadImg(){
    avatar.load("/home/alestru/PetProjects/RPG/img/player_avatar.png");


    playerPix[0].load("/home/alestru/PetProjects/RPG/img/player1.png");
    nothingPix.load("/home/alestru/PetProjects/RPG/img/nothing.png");
    shadowPix.load("/home/alestru/PetProjects/RPG/img/black.png");
    chestPix.load("/home/alestru/PetProjects/RPG/img/chest.png");

    cellPix[type_cell::wall].load("/home/alestru/PetProjects/RPG/img/wall.png");
    cellPix[type_cell::up_ladder].load("/home/alestru/PetProjects/RPG/img/ladder.png");
    cellPix[type_cell::down_ladder].load("/home/alestru/PetProjects/RPG/img/ladder.png");
    cellPix[type_cell::open_door].load("/home/alestru/PetProjects/RPG/img/open_door.png");
    cellPix[type_cell::close_door].load("/home/alestru/PetProjects/RPG/img/close_door.png");
    cellPix[type_cell::floor].load("/home/alestru/PetProjects/RPG/img/nothing.png");

    weaponPix[name_weapon::knife].load("/home/alestru/PetProjects/RPG/img/knife.png");
    weaponPix[name_weapon::sword].load("/home/alestru/PetProjects/RPG/img/sword.png");
    weaponPix[name_weapon::nunchucks].load("/home/alestru/PetProjects/RPG/img/nunchucks.png");

    equipmentPix[type_equipment::helmet].load("/home/alestru/PetProjects/RPG/img/helmet.png");
    equipmentPix[type_equipment::bib].load("/home/alestru/PetProjects/RPG/img/bib.png");
    equipmentPix[type_equipment::leggings].load("/home/alestru/PetProjects/RPG/img/leggings.png");
    equipmentPix[type_equipment::boots].load("/home/alestru/PetProjects/RPG/img/boots.png");

    bunchPix.load("/home/alestru/PetProjects/RPG/img/bunch.png");
    potionPix.load("/home/alestru/PetProjects/RPG/img/potion.png");

    mobPix[name_enemy::white_golem].load("/home/alestru/PetProjects/RPG/img/golem_npc.png");
    mobPix[name_enemy::black_druid].load("/home/alestru/PetProjects/RPG/img/druid_npc.png");
    mobPix[name_enemy::red_tiger].load("/home/alestru/PetProjects/RPG/img/tiger_npc.png");
    mobPix[name_enemy::blue_wolf].load("/home/alestru/PetProjects/RPG/img/wolf_npc.png");
}

void GameWindow::drawTools(){

    if (game.getDungeon().getHero().getWeapon() != nullptr){
        weaponSlot->setPixmap(weaponPix[game.getDungeon().getHero().getWeapon()->getWeapon_Name()].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
        if (game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact ||
            game.getDungeon().getHero().getWeapon()->getItem_Type() == type_item::weapon_artifact_enchantment){

            switch(dynamic_cast<WeaponArtifact *>(game.getDungeon().getHero().getWeapon())->getArtifact_Type()){
                case type_artifact::rare: weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed blue;"); break;
                case type_artifact::mythical: weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed purple;"); break;
                case type_artifact::legendary: weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed yellow;"); break;
                case type_artifact::casual: weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed black;"); break;
            }
        } else {
            weaponSlot->setStyleSheet("background-color: gray; border: 3px dashed white;");
        }
    }

    std::list<Equipment *> T = game.getDungeon().getHero().getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        int i;
        int j;
        switch((*iter)->getEquipment_Type()){
            case type_equipment::bib: i = 0; j = 0; break;
            case type_equipment::boots: i = 1; j = 0; break;
            case type_equipment::helmet:i = 0; j = 1; break;
            case type_equipment::leggings: i = 1; j = 1; break;
        }
        equipmentSlot[i][j]->setPixmap(equipmentPix[(*iter)->getEquipment_Type()].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));

        if ((*iter)->getItem_Type() == type_item::equipment_artifact){
            switch(static_cast<EquipmentArtifact *>(*iter)->getArtifact_Type()){
                case type_artifact::casual: equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed black;"); break;
                case type_artifact::rare: equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed blue;"); break;
                case type_artifact::mythical: equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed purple;"); break;
                case type_artifact::legendary: equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed yellow;"); break;
            }
        } else {
            equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed white;");
        }
    }
}

void GameWindow::drawInventory(){
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
                inventorySlot[i][j]->setPixmap(bunchPix.scaledToHeight(tileHeight));
            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::equipment ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::equipment_artifact){

                inventorySlot[i][j]->setPixmap(equipmentPix[dynamic_cast<Equipment *>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getEquipment_Type()].scaledToHeight(tileHeight));

            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::potion){
                inventorySlot[i][j]->setPixmap(potionPix.scaledToHeight(tileHeight));
            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact_enchantment ||
                     game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_enchantment){

                inventorySlot[i][j]->setPixmap(weaponPix[dynamic_cast<Weapon *>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getWeapon_Name()].scaledToHeight(tileHeight));
            }

            if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::equipment_artifact ||
                game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact ||
                game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItem_Type() == type_item::weapon_artifact_enchantment){

                switch(dynamic_cast<Artifact *>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getArtifact_Type()){
                    case type_artifact::casual: inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed black;"); break;
                    case type_artifact::rare: inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed blue;"); break;
                    case type_artifact::mythical: inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed purple;"); break;
                    case type_artifact::legendary: inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed yellow;"); break;
                }

            }

            if (game.getDungeon().getHero().getCurr_Chosen_Item() == 5 * (i + 1) - j - 1){
                inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed red;");
            }
        }
    }
}

void GameWindow::drawMob(){

    for (auto &i: game.getDungeon().getEnemies()){
        if (std::pow(game.getDungeon().getHero().getX() - i.second->getX(), 2) + std::pow(game.getDungeon().getHero().getY() - i.second->getY(), 2) > 36){
            tile[i.second->getX()][i.second->getY()]->setPixmap(shadowPix.scaledToHeight(tileHeight));
            hpTile[i.second->getX()][i.second->getY()]->setText("");
            continue;
        }
        if (i.first == game.getDungeon().getCur_Level()){
            tile[i.second->getX()][i.second->getY()]->setPixmap(mobPix[i.second->getName()].scaledToHeight(tileHeight));
            if (!i.second->isDead()){
                hpTile[i.second->getX()][i.second->getY()]->setText(QString::number(i.second->getCur_Hp()));
            } else{
                hpTile[i.second->getX()][i.second->getY()]->setText("DEAD");
            }
        }
    }

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

    drawTools();
    drawInventory();

    for (int i = 0; i < game.getMapHeight(); i++){
        for (int j = 0; j < game.getMapWidth(); j++){
            if (std::pow(game.getDungeon().getHero().getX() - i, 2) + std::pow(game.getDungeon().getHero().getY() - j, 2) > 36){

                tile[i][j]->setPixmap(shadowPix.scaledToHeight(tileHeight));
                hpTile[i][j]->setText("");
                continue;

            }
            if (i == game.getDungeon().getHero().getX() && j == game.getDungeon().getHero().getY()){

                tile[i][j]->setPixmap(playerPix[0].scaledToHeight(tileHeight));

            }
            else if (game.getDungeon().getLevels()[game.getDungeon().getCur_Level()][i][j].getChest() != nullptr){

                tile[i][j]->setPixmap(chestPix.scaledToHeight(tileHeight));

            }
            else if (game.getDungeon().getCurLevel()[i][j].getItem()){

                if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::bunch){

                    tile[i][j]->setPixmap(bunchPix.scaledToHeight(tileHeight));

                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::equipment_artifact){

                    tile[i][j]->setPixmap(equipmentPix[static_cast<Equipment *>(game.getDungeon().getCurLevel()[i][j].getItem())->getEquipment_Type()].scaledToHeight(tileHeight));
                }
                else if (game.getDungeon().getLevels()[game.getDungeon().getCur_Level()][i][j].getItem()->getItem_Type() == type_item::potion){

                    tile[i][j]->setPixmap(potionPix.scaledToHeight(tileHeight));

                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_artifact_enchantment ||
                         game.getDungeon().getCurLevel()[i][j].getItem()->getItem_Type() == type_item::weapon_enchantment){

                    tile[i][j]->setPixmap(weaponPix[static_cast<Weapon *>(game.getDungeon().getCurLevel()[i][j].getItem())->getWeapon_Name()].scaledToHeight(tileHeight));
                }
            }
            else{
                tile[i][j]->setPixmap(cellPix[game.getDungeon().getCurLevel()[i][j].getType()].scaledToHeight(tileHeight));
            }
            hpTile[i][j]->setText("");
        }
    }

    drawMob();
}

void GameWindow::act(std::string key){
    std::string command;
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
    else command = "invalid";


    if (command == "south" || command == "east" || command == "west" || command == "north"){

        type_destination destination;
        if (command == "south") destination = type_destination::south;
        else if (command == "east") destination = type_destination::east;
        else if (command == "west") destination = type_destination::west;
        else if (command == "north") destination = type_destination::north;
        game.getDungeon().getHero().move(destination, game.getDungeon());

    } else if (command == "action"){

        if (game.getDungeon().getHero().climb(game.getDungeon())) return;
        if (game.getDungeon().getHero().open_chest(game.getDungeon())) return;
        if (game.getDungeon().getHero().take(game.getDungeon())) return;
        if (game.getDungeon().getHero().change_door(game.getDungeon())) return;

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
        else if (command == "intelligence") up = short_characteristic::i;
        else if (command == "agility") up = short_characteristic::a;
        else if (command == "endurance") up = short_characteristic::e;
        game.getDungeon().getHero().levelUp(up);

    } else if (command == "use"){
        game.getDungeon().getHero().usingChosenItem(game.getDungeon());
    }
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

