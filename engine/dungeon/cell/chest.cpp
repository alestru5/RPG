#include "chest.h"
#include "../../character/hero/hero.h"

Chest::Chest(int l, Item *I){
    if (l <= 0 || l > 5){
        throw std::invalid_argument("level is not in 1-5");
    }
    level = l;
    item = I;
}

Chest& Chest::setLevel(int l){
    if (l <= 0 || l > 5){
        throw std::invalid_argument("level is not in 1-5");
    }
    level = l;
    return *this;
}

std::pair<bool, bool> Chest::tryToOpen(Hero *H) const noexcept{
    int intelligence = H->getTable().getValue("intelligence");
    int chance = intelligence;
    if (rand() % 100 <= chance / level){
        return std::make_pair(true, true);
    }
    if (rand() % 100 <= chance){
        return std::make_pair(false, false);
    }
    return std::make_pair(false, true);
}

Chest& Chest::operator =(const Chest &C){
    if (this != &C){
        level = C.level;
        item = C.item;
    }
    return *this;
}
