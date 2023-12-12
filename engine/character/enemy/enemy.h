#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <semaphore>

#include "../character.h"
#include "../../helps/enums.h"
#include "../../helps/sets/setdamage.h"
#include "../../item/item.h"

class Item;

class Enemy: public Character{
private:
    name_enemy name;
    int min_damage;
    int max_damage;
    Item *item;

public:
    Enemy() noexcept;
    Enemy(int i, int j) noexcept;
    Enemy(int i, int j, name_enemy n) noexcept;

    ~Enemy() { delete item; }

    name_enemy getName() const noexcept { return name; }
    Item* getItem() const noexcept { return item; }

    Enemy& setName(name_enemy n) noexcept { name = n; return *this; }
    Enemy& setItem(Item *I) noexcept { item = I; return *this; }
    Enemy& setExperience(int exp);

    bool findEnemy(Dungeon &dungeon, int i, int j);
    bool isNear(Dungeon &dungeon) const noexcept;
    type_destination vision(Dungeon &dungeon) const noexcept;
    void move(type_destination direction, Dungeon &dungeon) noexcept override;
    void randomMoveMob(Dungeon &dungeon) noexcept;
    void dropItem(Dungeon &dungeon) noexcept;

    void getDamage(int damage) override;
    void attack(Character *C) override;

};

#endif // ENEMY_H