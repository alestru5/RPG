#ifndef CHARACTER_H
#define CHARACTER_H

#include<vector>
#include<string>
#include<atomic>

#include "../helps/enums.h"

class Dungeon;
class Item;

class Character{
    protected:
        int max_hp;
        int cur_hp;
        std::atomic<int> x;
        std::atomic<int> y;

    public:
        Character() noexcept: max_hp(100), cur_hp(100), x(-1), y(-1) {}

        void setX(int i);
        void setY(int j);
        void setMax_Hp(int hp);
        void setCur_Hp(int hp);

        int getX() const noexcept {return x; }
        int getY() const noexcept {return y; }
        int getMax_Hp() const noexcept { return max_hp; }
        int getCur_Hp() const noexcept { return cur_hp; }

        bool isDead() const noexcept { return cur_hp <= 0; }

        virtual void getDamage(int damage) = 0;
        virtual void attack(Character *C) = 0;
        virtual void move(type_destination d, Dungeon &dungeon) noexcept = 0;

};

#endif // CHARACTER_H
