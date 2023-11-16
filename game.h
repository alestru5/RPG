#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>

#include "dungeon.h"
#include "hero.h"


class Game{
    private:
        Dungeon dungeon;
        int mapWidth;
        int mapHeight;
        bool isGame;

    public:
        Game(): mapWidth(32), mapHeight(16), isGame(false), dungeon() { }

        Dungeon &getDungeon() noexcept { return dungeon; }
        int getMapWidth() const noexcept { return mapWidth; }
        int getMapHeight() const noexcept { return mapHeight; }
        bool getIsGame() const noexcept { return isGame; }

        Game &setMapWidth(int mW) noexcept { mapWidth = mW; return *this; }
        Game &setMapHeight(int mH) noexcept { mapHeight = mH; return *this; }

        void initGame();
        bool tick(Dungeon &dungeon);

        void actionMobs(Dungeon &dungeon);
};

#endif // GAME_H
