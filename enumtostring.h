#ifndef ENUMTOSTRING_H
#define ENUMTOSTRING_H
#include "enums.h"
#include "iostream"
class EnumToString{
    public:
        static std::string toString(name_weapon n);
        static std::string toString(name_equipment n, type_equipment t);
        static std::string toString(name_potion n);
};

#endif // ENUMTOSTRING_H
