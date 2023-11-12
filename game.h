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
        static type_destination vision(Enemy *E);
        static void moveMobDestination(Enemy *E, type_destination d);
        static void randomMoveMob(Enemy *E);
};

#endif // GAME_H
