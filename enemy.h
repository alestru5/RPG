#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "enums.h"
#include "setdamage.h"
#include "item.h"
class Enemy: public Character{
private:
    name_enemy name;
    int min_damage;
    int max_damage;
    Item *item;

public:
    Enemy();
    Enemy(int i, int j);
    Enemy(int i, int j, name_enemy n);

    name_enemy getName() const noexcept { return name; }
    Item* getItem() const noexcept { return item; }

    Enemy& setName(name_enemy n) noexcept { name = n; return *this; }
    Enemy& setItem(Item *I) noexcept { item = I; return *this; }
    Enemy& setExperience(int exp);


};

#endif // ENEMY_H
