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

bool Game::tick(){
    if (isGame){
        moveMobs();
        return true;
    } else{
        return false;
    }

}

void Game::moveMobs(){
    for (size_t i = 0; i < dungeon.getEnemies().size(); i++){
        if (dungeon.getEnemies()[i].first == dungeon.getCur_Level()){
            type_destination destination = vision(dungeon.getEnemies()[i].second);
            if (destination != type_destination::none){
                moveMobDestination(dungeon.getEnemies()[i].second, destination);
            }
            else if (!(dungeon.getEnemies()[i].second->getX() == dungeon.getHero().getX() &&
                         dungeon.getEnemies()[i].second->getY() == dungeon.getHero().getY())){
                randomMoveMob(dungeon.getEnemies()[i].second);
            } else{
                Game::isGame = false;
            }
        }
    }
}

type_destination Game::vision(Enemy *E){
    int x = E->getX();
    int y = E->getY();
    int hx = dungeon.getHero().getX();
    int hy = dungeon.getHero().getY();
    if (abs(hx - x) >= 5 || abs(hy - y) >= 5){
        return type_destination::none;
    }
    for (int i = std::min(x, hx); i < std::max(x, hx) + 1; i++){
        double j;
        if (hx + 1 - x != 0){
            j = static_cast <double> ((i - x) * (hy + 1 - y) / (hx + 1 - x)) + static_cast<double> (y);
        } else{
            j = hy + 1;
        }

        int u_j = std::floor(j + 1.);
        for (int k = std::min(y, hy); k < u_j; k++){
            if (dungeon.getCurLevel()[i][k].isWall() || dungeon.getCurLevel()[i][k].getType() == type_cell::close_door ||
                dungeon.getCurLevel()[i][k].getItem() != nullptr || dungeon.getCurLevel()[i][k].isChest()){
                return type_destination::none;
            }
        }
    }

    Cell destination = dungeon.getCurLevel()[x-1][y];
    if (x > hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::north;
    }
    destination = dungeon.getCurLevel()[x+1][y];
    if (x < hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::south;
    }
    destination = dungeon.getCurLevel()[x][y+1];
    if (y < hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::east;
    }
    destination = dungeon.getCurLevel()[x][y-1];
    if (y > hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::west;
    }
    return type_destination::none;
}

void Game::moveMobDestination(Enemy *E, type_destination d){
    if (d == type_destination::north){
        E->setX(E->getX() - 1);
    } else if (d == type_destination::south){
        E->setX(E->getX() + 1);
    } else if (d == type_destination::east){
        E->setY(E->getY() + 1);
    } else if (d == type_destination::west){
        E->setY(E->getY() - 1);
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

