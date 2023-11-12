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
    if (dungeon.getHero().isDead()){
        isGame = false;
    }
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
            type_destination destination = dungeon.getEnemies()[i].second->vision();
            if (destination != type_destination::none){
                dungeon.getEnemies()[i].second->moveMobDestination(destination);
            }
            else if (!dungeon.getEnemies()[i].second->isNear()){
                dungeon.getEnemies()[i].second->randomMoveMob();
            } else if (dungeon.getEnemies()[i].second->isNear()){
                dungeon.getEnemies()[i].second->enemyAtack();
            }
        }
    }
}



