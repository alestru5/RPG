#include "game.h"

void Game::initGame(){
    try{
        std::ifstream lvl;
        lvl.open("/home/alestru/PetProjects/RPG/map.txt");
        dungeon.initializeLevelsFile(lvl, *this);
        lvl.close();

        std::ifstream mobs;
        mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
        dungeon.initializeEnemiesFile(mobs);
        mobs.close();

        isGame = true;
    } catch(...){
        throw;
    }

}

bool Game::tick(Dungeon &dungeon){
    try{
        if (dungeon.getHero().isDead()){
            isGame = false;
        }
        if (isGame){
            actionMobs(dungeon);
            dungeon.getHero().updateEndurance();
            return true;
        } else{
            return false;
        }
    } catch(...){
        throw;
    }
}

void Game::actionMobs(Dungeon &dungeon){
    try{
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
    } catch(...){
        throw;
    }

}




