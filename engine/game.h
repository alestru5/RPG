#ifndef GAME_H
#define GAME_H

#include <thread>
#include <mutex>

#include "./dungeon/dungeon.h"


class Game{
    private:
        Dungeon dungeon;
        int mapWidth;
        int mapHeight;
        bool isGame;

    public:
        Game(): mapWidth(320), mapHeight(160), isGame(false), dungeon() { }

        Dungeon &getDungeon() noexcept { return dungeon; }
        int getMapWidth() const noexcept { return mapWidth; }
        int getMapHeight() const noexcept { return mapHeight; }
        bool getIsGame() const noexcept { return isGame; }

        Game &setMapWidth(int mW) noexcept { mapWidth = mW; return *this; }
        Game &setMapHeight(int mH) noexcept { mapHeight = mH; return *this; }
        Game &setisGame(bool status) noexcept { isGame = status; return *this;}
        void initGame();
        bool tick(Dungeon &dungeon);

        void actionMobs(int i, int j);
};

#endif // GAME_H
