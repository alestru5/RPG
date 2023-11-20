#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include<string>

#include "enums.h"


class Dungeon;

class Character{
    protected:
        int experience;
        int max_hp;
        int cur_hp;
        int x;
        int y;

    public:
        Character() noexcept: experience(), max_hp(100), cur_hp(100), x(-1), y(-1) {}

        void setX(int i);
        void setY(int j);
        void setExperience(int exp);
        void setMax_Hp(int hp);
        void setCur_Hp(int hp);

        int getX() const noexcept {return x; }
        int getY() const noexcept {return y; }
        int getExperience() const noexcept { return experience; }
        int getMax_Hp() const noexcept { return max_hp; }
        int getCur_Hp() const noexcept { return cur_hp; }

        bool isDead() const noexcept { return cur_hp <= 0; }

        virtual void getDamage(int damage) = 0;
        virtual void attack(Character *C) = 0;
        virtual void move(type_destination d, Dungeon &dungeon) noexcept = 0;

};

#endif // CHARACTER_H
