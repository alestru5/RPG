#include "game.h"
Dungeon Game::dungeon;
int Game::mapWidth = 32;
int Game::mapHeight = 16;
bool Game::isGame = false;

void Game::initGame(){
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    dungeon.initializeLevelsFile(lvl);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    dungeon.initializeEnemiesFile(mobs);
    mobs.close();

    isGame = true;

}

void Game::tick(){
    if (isGame){
        moveMobs();
    } else{

    }

}

void Game::moveMobs(){
    for (size_t i = 0; i < dungeon.getEnemies().size(); i++){
        if (dungeon.getEnemies()[i].first == dungeon.getCur_Level()){
            randomMoveMob(dungeon.getEnemies()[i].second);
        }
    }
}

void Game::randomMoveMob(Enemy *E){
    int a = rand() % 4;
    Cell destination = dungeon.getCurLevel()[E->getX() - 1][E->getY()];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr)){
        E->setX(E->getX()-1);
        return;
    }
    a = rand() % 3;
    destination = dungeon.getCurLevel()[E->getX()+1][E->getY()];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        E->setX(E->getX()+1);
        return;
    }
    a = rand() % 2;
    destination = dungeon.getCurLevel()[E->getX()][E->getY()+1];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        E->setY(E->getY()+1);
        return;
    }
    destination = dungeon.getCurLevel()[E->getX()][E->getY()-1];
    if ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr){
        E->setY(E->getY()-1);
    }
}

