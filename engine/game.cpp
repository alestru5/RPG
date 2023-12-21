#include "game.h"

void Game::initGame(std::ifstream& map, const json& config, std::string pluginsDir){
    try{
        manager.scan(pluginsDir, ".so");
        for(auto& pluginInfo : manager.getPlugins()) {
            Item& plugin = pluginInfo.second.plugin;
            pluginByItem.insert({plugin.getItemType(), std::ref(plugin)});
        }
        dungeon.initializeLevelsFile(map, config, *this);
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
            auto threadNum = std::thread::hardware_concurrency();
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
            dungeon.getHero().setCur_Endurance(std::min(dungeon.getHero().getCur_Endurance() + 10, dungeon.getHero().getTable().getValue("e")));
            dungeon.getHero().setCur_Hp(std::min(dungeon.getHero().getCur_Hp() + 1, dungeon.getHero().getMax_Hp()));
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

void Game::saveGame(std::ofstream &map){
    dungeon.saveLevelsFile(map, *this);
}




