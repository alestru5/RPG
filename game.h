#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>

#include "dungeon.h"
#include "hero.h"
#include "gamewindow.h"


class Game{
    public:
        static Dungeon dungeon;
        static int mapWidth;
        static int mapHeight;
        static bool isGame;

        static void initGame();
        static bool tick();

        static void moveMobs();

};

#endif // GAME_H
