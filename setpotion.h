#ifndef SETPOTION_H
#define SETPOTION_H
#include <iostream>
#include <list>
#include "enums.h"
class SetPotion{
    public:
        static std::pair<changes_characteristic, int> createChanges(name_potion N);
};

#endif // SETPOTION_H
