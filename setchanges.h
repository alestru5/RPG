#ifndef SETCHANGES_H
#define SETCHANGES_H

#include <iostream>
#include <list>
#include "enums.h"

class SetChanges{
    public:
        static std::list<std::pair<short_characteristic, int>> createChanges(type_artifact T);
};

#endif // SETCHANGES_H
