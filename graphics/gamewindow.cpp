#include "gamewindow.h"

void GameWindow::pause()
{
    if (pauseMenu->isVisible()){
        pauseMenu->hide();
        timer = startTimer(1000);
    } else{
        pauseMenu->showFullScreen();
        killTimer(timer);
    }
}

void GameWindow::endGame(){
    hide();
    game.setisGame(false);
    emit quitGame();
}

void GameWindow::saveGame(){
    QString path = "/home/alestru/PetProjects/RPG/Maps";
    QDir directory(path);
    if (!directory.exists()) {
        return;
    }
    QStringList list = directory.entryList(QDir::Files);
    QString count = "1";
    for (int i = 0; i < list.size(); ++i) {
        QString filename = list.at(i);
        if (filename.toStdString().find("Saved") != std::string::npos && filename.toStdString().find(".txt") != std::string::npos){
            count = filename.split(".")[0];
            count = count.split("Saved")[1];
        }
    }
    std::string newName = "Saved" + std::to_string(count.toInt() +1) + ".txt";
    std::ofstream newFile((path + "/").toStdString() + newName);
    game.saveGame(newFile);
    newFile.close();
}

void GameWindow::setSize(){
    this->setFixedSize(1920,1080);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}
GameWindow::GameWindow(QMainWindow *parent): QMainWindow(parent){}

void GameWindow::start(std::ifstream &in, const json& config){
    setWindowTitle("Vagabund");
    pauseMenu = new PauseMenu(this);
    connect(pauseMenu, &PauseMenu::resumeGame, this, &GameWindow::pause);
    connect(pauseMenu, &PauseMenu::endGame, this, &GameWindow::endGame);
    connect(pauseMenu, &PauseMenu::saveGame, this, &GameWindow::saveGame);
    pauseMenu->hide();
    pauseMenu->setWindowFlags(Qt::Tool | Qt::Window | Qt::FramelessWindowHint);

    playerPix.resize(1);

    loadImg();

    info = new QLabel(this);
    info->setGeometry(0, 0, 1920, infoHeight);
    info->setStyleSheet("background-color: #000000; border-bottom: 10 px white;");


    QLabel *avatarLabel = new QLabel(this);
    avatarLabel->setGeometry(10, 10, 50, 50);
    avatarLabel->setPixmap(avatar.scaledToHeight(50));

    bar = new QGraphicsView(this);
    bar->setGeometry(70, 0, 4 * tileHeight, infoHeight / 2);
    bar->setBackgroundBrush(Qt::black);
    bar->setFrameShape(QFrame::NoFrame);
    bar->setScene(new QGraphicsScene(this));

    hpBar = new QGraphicsRectItem(0, 0, 4 * tileHeight, infoHeight / 4);
    hpBar->setPen(Qt::NoPen);
    hpBar->setBrush(Qt::red);

    eBar = new QGraphicsRectItem(0, infoHeight / 4, 4 * tileHeight, infoHeight / 4);
    eBar->setPen(Qt::NoPen);
    eBar->setBrush(Qt::green);

    bar->scene()->addItem(hpBar);
    bar->scene()->addItem(eBar);

    game.initGame(in, config);

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
            equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid white;");
        }
    }

    weaponSlot = new QLabel(this);
    weaponSlot->setGeometry((game.getMapWidth() - 1) * tileHeight  - 9 * tileHeight - 5 * tileHeight / 16, 0, tileHeight * 31 / 32, tileHeight * 31 / 32);
    weaponSlot->setStyleSheet("background-color: gray; border: 3px solid white;");

    bunchSlot = new QLabel(this);
    bunchSlot->setGeometry((game.getMapWidth() - 1) * tileHeight  - 11 * tileHeight - 5 * tileHeight / 16, 0, tileHeight * 31 / 32, tileHeight * 31 / 32);
    bunchSlot->setStyleSheet("background-color: gray; border: 3px solid white;");
    bunchSlot->setPixmap(bunchPix.scaled(tileHeight, tileHeight * 31 / 32));

    bunchCount = new QLabel(this);
    bunchCount->setGeometry((game.getMapWidth() - 1) * tileHeight  - 11 * tileHeight - 5 * tileHeight / 16, tileHeight * 17/16, tileHeight * 31 / 32, tileHeight * 31 / 32);
    bunchCount->setStyleSheet("background-color: gray; border: 3px solid white; font-size: 35px; text-align: center; color: white");

    characteristicSlots.push_back(std::vector<QLabel*>(8));
    for (int i = 0; i <= characteristicSlots.size()-1; i++){
        for (int j = 0; j <= characteristicSlots[i].size()-1; j++){
            characteristicSlots[i][j] = new QLabel(this);
            characteristicSlots[i][j]->setFrameShape(QFrame::NoFrame);
            characteristicSlots[i][j]->setGeometry((game.getMapWidth() - 1) * tileHeight  - 23 * tileHeight - 6 * tileHeight / 16 + (j + static_cast<int>(j>=2) + static_cast<int>(j>=4) + static_cast<int>(j>=6)) * tileHeight, 0, tileHeight, tileHeight * 31 / 32);
            if (i == 0 && j == 1){
                characteristicSlots[i][j]->setStyleSheet("background-color: red; font-size: 35px; text-align: center; color: black; position: absolute;");
            } else if (i == 0 && j == 3){
                characteristicSlots[i][j]->setStyleSheet("background-color: #00ff00; font-size: 35px; text-align: center; color: black;");
            } else if (i == 0 && j == 5){
                characteristicSlots[i][j]->setStyleSheet("background-color: blue; font-size: 35px; text-align: center; color: black;");
            } else if (i == 0 && j == 7){
                characteristicSlots[i][j]->setStyleSheet("background-color: #14b814; font-size: 35px; text-align: center; color: black;");
            }
            if (i == 0 && j == 0){
                characteristicSlots[i][j]->setStyleSheet("background-color: red;");
                characteristicSlots[i][j]->setPixmap(characteristicPix["strength"].scaled(tileHeight, tileHeight * 31 / 32));
            } else if (i == 0 && j == 2){
                characteristicSlots[i][j]->setStyleSheet("background-color: #00ff00;");
                characteristicSlots[i][j]->setPixmap(characteristicPix["agility"].scaled(tileHeight, tileHeight * 31 / 32));
            } else if (i == 0 && j == 4){
                characteristicSlots[i][j]->setStyleSheet("background-color: blue; font-size: 35px; text-align: center; color: white");
                characteristicSlots[i][j]->setPixmap(characteristicPix["intelligence"].scaled(tileHeight, tileHeight * 31 / 32));
            } else if(i == 0 && j == 6){
                characteristicSlots[i][j]->setStyleSheet("background-color: #14b814; font-size: 35px; text-align: center; color: white");
                characteristicSlots[i][j]->setPixmap(characteristicPix["experience"].scaled(tileHeight, tileHeight * 31 / 32));
            }

        }
    }

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

    weaponPix["knife"].load("/home/alestru/PetProjects/RPG/img/knife.png");
    weaponPix["sword"].load("/home/alestru/PetProjects/RPG/img/sword.png");
    weaponPix["nunchucks"].load("/home/alestru/PetProjects/RPG/img/nunchucks.png");

    characteristicPix["strength"].load("/home/alestru/PetProjects/RPG/img/strength.png");
    characteristicPix["agility"].load("/home/alestru/PetProjects/RPG/img/agility.png");
    characteristicPix["intelligence"].load("/home/alestru/PetProjects/RPG/img/intelligence.png");
    characteristicPix["experience"].load("/home/alestru/PetProjects/RPG/img/experience.png");

    equipmentPix["helmet"].load("/home/alestru/PetProjects/RPG/img/helmet.png");
    equipmentPix["bib"].load("/home/alestru/PetProjects/RPG/img/bib.png");
    equipmentPix["leggings"].load("/home/alestru/PetProjects/RPG/img/leggings.png");
    equipmentPix["boots"].load("/home/alestru/PetProjects/RPG/img/boots.png");

    bunchPix.load("/home/alestru/PetProjects/RPG/img/bunch.png");
    potionPix.load("/home/alestru/PetProjects/RPG/img/potion.png");

    mobPix[name_enemy::white_golem].load("/home/alestru/PetProjects/RPG/img/golem_npc.png");
    mobPix[name_enemy::black_druid].load("/home/alestru/PetProjects/RPG/img/druid_npc.png");
    mobPix[name_enemy::red_tiger].load("/home/alestru/PetProjects/RPG/img/tiger_npc.png");
    mobPix[name_enemy::blue_wolf].load("/home/alestru/PetProjects/RPG/img/wolf_npc.png");
}

void GameWindow::drawTools(){

    if (game.getDungeon().getHero().getWeapon() != nullptr){
        weaponSlot->setPixmap(weaponPix[(game.getDungeon().getHero().getWeapon())->getItemName()].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));
        if (game.getDungeon().getHero().getWeapon()->getItemType().find("artifact") != std::string::npos){
            std::string at = QString::fromStdString((game.getDungeon().getHero().getWeapon()->getItemName())).split("_")[1].toStdString();
            if (at == "rare") weaponSlot->setStyleSheet("background-color: gray; border: 3px solid blue;");
            if (at == "mythical") weaponSlot->setStyleSheet("background-color: gray; border: 3px solid  purple;");
            if (at == "legendary") weaponSlot->setStyleSheet("background-color: gray; border: 3px solid yellow;");
            if (at == "casual") weaponSlot->setStyleSheet("background-color: gray; border: 3px solid black;");
        } else {
            weaponSlot->setStyleSheet("background-color: gray; border: 3px solid white;");
        }
    }

    std::list<Item *> T = game.getDungeon().getHero().getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        int i;
        int j;
        std::string et = QString::fromStdString((*iter)->getItemName()).split("_")[1].toStdString();
        if (et == "bib"){
            i = 0; j = 0;
        }
        if (et == "boots"){
            i = 1; j = 0;
        }
        if (et == "helmet"){
            i = 0; j = 1;
        }
        if (et == "leggings"){
            i = 1; j = 1;
        }
        equipmentSlot[i][j]->setPixmap(equipmentPix[QString::fromStdString((*iter)->getItemName()).split("_")[1].toStdString()].scaled(tileHeight * 31 / 32, tileHeight * 31 / 32));

        if ((*iter)->getItemType().find("artifact") != std::string::npos){
            std::string at = QString::fromStdString((*iter)->getItemName()).split("_")[2].toStdString();
            if (at == "casual") equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid black;");
            if (at == "rare") equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid blue;");
            if (at == "mythical") equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid purple;");
            if (at == "legendary") equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid yellow;");
        } else {
            equipmentSlot[i][j]->setStyleSheet("background-color: gray; border: 3px solid white;");
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

            if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemType() == "bunch"){
                inventorySlot[i][j]->setPixmap(bunchPix.scaledToHeight(tileHeight));
            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemType().find("equipment") != std::string::npos){
                inventorySlot[i][j]->setPixmap(equipmentPix[QString::fromStdString(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemName()).split("_")[1].toStdString()].scaledToHeight(tileHeight));
            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemType() == "potion"){
                inventorySlot[i][j]->setPixmap(potionPix.scaledToHeight(tileHeight));
            }

            else if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemType().find("weapon") != std::string::npos){
                inventorySlot[i][j]->setPixmap(weaponPix[QString::fromStdString((game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getItemName()).split("_")[0].toStdString()].scaledToHeight(tileHeight));
            }

            if (game.getDungeon().getHero().getInventory()[5*(i+1)-j-1]->getItemType().find("artifact") != std::string::npos){
                std::string at = dynamic_cast<Artifact *>(game.getDungeon().getHero().getInventory()[5*(i+1)-j-1])->getArtifact_Type();
                if (at == "casual") inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed black;");
                if (at == "rare") inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed blue;");
                if (at == "mythical") inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed purple;");
                if (at == "legendary") inventorySlot[i][j]->setStyleSheet("background-color: gray; border: 3px dashed yellow;");
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

void GameWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0 && event->delta()<150){
        act("wheelUp");
    } else if (event->delta() < 0 && event->delta() > -150){
        act("wheelDown");
    }
}

void GameWindow::keyPressEvent(QKeyEvent* e){

    if (e->key() == Qt::Key_Escape){
        pause();
    }
    std::string key = e->text().toLocal8Bit().constData();
    act(key);

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
    update();
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
    hpBar->setRect(0, 0, static_cast<double>(game.getDungeon().getHero().getCur_Hp()) / static_cast<double>(game.getDungeon().getHero().getMax_Hp()) * 4. * static_cast<double>(tileHeight), infoHeight/4);
    eBar->setRect(0, infoHeight / 4, static_cast<double>(game.getDungeon().getHero().getCur_Endurance()) / static_cast<double>(game.getDungeon().getHero().getTable().getValue("e")) * 4. * static_cast<double>(tileHeight), infoHeight/4);

    bunchCount->setText(QString::fromStdString(std::to_string(game.getDungeon().getHero().getC_Bunch())));

    characteristicSlots[0][1]->setText(QString::fromStdString(" " + std::to_string(game.getDungeon().getHero().getTable().getValue("s"))));
    characteristicSlots[0][3]->setText(QString::fromStdString(" " + std::to_string(game.getDungeon().getHero().getTable().getValue("a"))));
    characteristicSlots[0][5]->setText(QString::fromStdString(" " + std::to_string(game.getDungeon().getHero().getTable().getValue("i"))));
    characteristicSlots[0][7]->setText(QString::fromStdString(std::to_string(game.getDungeon().getHero().getTable().getValue("exp"))));
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

                if (game.getDungeon().getCurLevel()[i][j].getItem()->getItemType() == "bunch"){

                    tile[i][j]->setPixmap(bunchPix.scaledToHeight(tileHeight));

                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItemType().find("equipment") != std::string::npos){

                    tile[i][j]->setPixmap(equipmentPix[QString::fromStdString(game.getDungeon().getCurLevel()[i][j].getItem()->getItemName()).split("_")[1].toStdString()].scaledToHeight(tileHeight));
                }
                else if (game.getDungeon().getLevels()[game.getDungeon().getCur_Level()][i][j].getItem()->getItemType() == "potion"){
                    tile[i][j]->setPixmap(potionPix.scaledToHeight(tileHeight));
                }
                else if (game.getDungeon().getCurLevel()[i][j].getItem()->getItemType().find("weapon") != std::string::npos){
                    tile[i][j]->setPixmap(weaponPix[(game.getDungeon().getCurLevel()[i][j].getItem())->getItemName()].scaledToHeight(tileHeight));
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
    else if (key == "wheelUp") command = key;
    else if (key == "wheelDown") command = key;
    else return;


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

    } else if (command == "strength" || command == "intelligence" || command == "agility" || command == "endurance"){

        std::string up;
        if (command == "strength") up = "s";
        else if (command == "intelligence") up = "i";
        else if (command == "agility") up = "a";
        else if (command == "endurance") up = "e";
        game.getDungeon().getHero().levelUp(up);

    } else if (command == "use"){
        game.getDungeon().getHero().usingChosenItem(game.getDungeon());
    } else if (command == "wheelUp"){
        game.getDungeon().getHero().nextChosenItem();
    } else if (command == "wheelDown"){
        game.getDungeon().getHero().prevChosenItem();
    }
    drawGame();
}



