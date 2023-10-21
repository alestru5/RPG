#ifndef GAME_H
#define GAME_H


#include "dungeon.h"
#include "hero.h"

class Hero;
class Character;

class Game{
    public:
        Game();
        static Dungeon dungeon;
        static Hero hero;
        static int mapWidth;
        static int mapHeight;
};

#endif // GAME_H
