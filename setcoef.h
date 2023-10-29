#ifndef SETCOEF_H
#define SETCOEF_H

#include <iostream>
#include <list>
#include "enums.h"

class SetCoef{
    public:
        static std::list<std::pair<trait, double>> createCoef(type_enchantment T);

};

#endif // SETCOEF_H
