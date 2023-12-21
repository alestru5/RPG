#ifndef GAME_H
#define GAME_H

#include <thread>
#include <functional>
#include <iostream>

#include "./dungeon/dungeon.h"
#include "./item/PluginManager/plugin_manager.h"

class Game{
    private:
        Dungeon dungeon;
        int mapWidth;
        int mapHeight;
        bool isGame;
        std::unordered_map<std::string, std::reference_wrapper<Item>>pluginByItem;
    public:
        Game(): mapWidth(32), mapHeight(16), isGame(false), dungeon(){ }

        Dungeon &getDungeon() noexcept { return dungeon; }
        int getMapWidth() const noexcept { return mapWidth; }
        int getMapHeight() const noexcept { return mapHeight; }
        bool getIsGame() const noexcept { return isGame; }
        std::unordered_map<std::string, std::reference_wrapper<Item>> getPlugins() noexcept { return pluginByItem; }

        Game &setMapWidth(int mW) noexcept { mapWidth = mW; return *this; }
        Game &setMapHeight(int mH) noexcept { mapHeight = mH; return *this; }
        Game &setisGame(bool status) noexcept { isGame = status; return *this;}

        bool tick(Dungeon &dungeon);

        void actionMobs(int i, int j);

        void initGame(std::ifstream& map, const json& config, std::string pluginsDir);
        void saveGame(std::ofstream& map);
};

#endif // GAME_H
