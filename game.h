#ifndef GAME_H
#define GAME_H

#include "dungeon.h"
#include "hero.h"



class Game{
    public:
        static Dungeon dungeon;
        static int mapWidth;
        static int mapHeight;
};

#endif // GAME_H
