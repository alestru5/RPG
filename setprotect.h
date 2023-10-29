#ifndef SETPROTECT_H
#define SETPROTECT_H

#include <iostream>
#include "enums.h"

class SetProtect{
    public:
        static std::pair<int, int> createProtect(name_equipment N, type_equipment T);
        static int setBonus_Protect(type_artifact T);
};

#endif // SETPROTECT_H
