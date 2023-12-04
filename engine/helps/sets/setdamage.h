#ifndef SETDAMAGE_H
#define SETDAMAGE_H

#include <iostream>

#include "../enums.h"

class SetDamage{
    public:
        static std::pair<int, int> createDamage(name_weapon n);
        static int setBonus_Damage(type_artifact T);
        static std::pair<int, int> createDamage(name_enemy n);
};

#endif // SETDAMAGE_H
