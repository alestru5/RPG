#ifndef CHEST_H
#define CHEST_H

#include <iostream>

#include "../../item/item.h"

class Hero;

class Chest{
    private:
        int level;
        Item *item;

    public:
        Chest() noexcept: level(1), item(nullptr) {}
        Chest(int l, Item *I);

        int getLevel() const noexcept { return level; }
        Item *getItem() const noexcept { return item; }

        Chest& setLevel(int l);
        Chest& setItem(Item *I) { item = I; return *this; }

        std::pair<bool, bool> tryToOpen(Hero *H) const noexcept;

        Chest& operator =(const Chest &C);
};

#endif // CHEST_H
