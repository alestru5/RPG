#include "game.h"

void Game::initGame(){
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    dungeon.initializeLevelsFile(lvl, *this);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    dungeon.initializeEnemiesFile(mobs, *this);
    mobs.close();

    isGame = true;

}

bool Game::tick(Dungeon &dungeon){
    if (dungeon.getHero().isDead()){
        isGame = false;
    }
    if (isGame){
        moveMobs(dungeon);
        dungeon.getHero().updateEndurance();
        return true;
    } else{
        return false;
    }

}

void Game::moveMobs(Dungeon &dungeon){
    for (size_t i = 0; i < dungeon.getEnemies().size(); i++){
        if (dungeon.getEnemies()[i].first == dungeon.getCur_Level()){
            type_destination destination = dungeon.getEnemies()[i].second->vision(dungeon);
            if (destination != type_destination::none){
                dungeon.getEnemies()[i].second->move(destination, dungeon);
            }
            else if (!dungeon.getEnemies()[i].second->isNear(dungeon)){
                dungeon.getEnemies()[i].second->randomMoveMob(dungeon);
            } else if (dungeon.getEnemies()[i].second->isNear(dungeon)){
                dungeon.getEnemies()[i].second->attack(&static_cast<Character&>(dungeon.getHero()));
            }
        }
    }
}



