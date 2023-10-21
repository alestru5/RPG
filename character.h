#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include<string>

#include "cell.h"
#include "dungeon.h"

class Dungeon;

class Character{
    protected:
        /*Table characteristic;
         * Weapon weapon;
         * Equipment equipment[4]
         * Potion potion */
        int x;
        int y;
    public:
        Character(): x(0), y(0){};
        Character(int i, int j);
        bool move(std::string direction);
};

#endif // CHARACTER_H
