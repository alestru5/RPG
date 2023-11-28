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

        isGame = false;
    } catch(...){
        throw;
    }

}

bool Game::tick(Dungeon &dungeon){
    try{
        if (dungeon.getHero().isDead() || dungeon.getEnemies().size() == 0){
            isGame = false;
        }
        if (isGame){
            auto threadNum = 2;
            std::cout<<threadNum<<"----"<<std::endl;
            std::vector<std::thread> threads(threadNum);
            int elements = dungeon.getEnemies().size();
            for (size_t i = 0; i < threadNum; ++i) {
                int start_i = i * elements / threadNum;
                int end_i = (i + 1) * elements / threadNum;
                threads[i] = std::thread([=](){actionMobs(start_i, end_i);});

            }
            for(auto& th : threads) {
                th.join();
            }
            dungeon.getHero().updateEndurance();
            return true;
        } else{
            return false;
        }
    } catch(...){
        throw;
    }
}

void Game::actionMobs(int i, int j){
    try{
        std::cout<<i<<" "<<j<<std::endl;
        for (int k = i; k < j; k++){
            if (dungeon.getEnemies()[k].first == dungeon.getCur_Level()){
                type_destination destination = dungeon.getEnemies()[i].second->vision(dungeon);
                if (destination != type_destination::none){
                    dungeon.getEnemies()[k].second->move(destination, dungeon);
                }
                else if (!dungeon.getEnemies()[k].second->isNear(dungeon)){
                    dungeon.getEnemies()[k].second->randomMoveMob(dungeon);
                } else if (dungeon.getEnemies()[k].second->isNear(dungeon)){
                    dungeon.getEnemies()[k].second->attack(&static_cast<Character&>(dungeon.getHero()));
                }
            }
        }
    } catch(...){
        throw;
    }

}




