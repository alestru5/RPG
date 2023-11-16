#ifndef ITEM_H
#define ITEM_H

#include "enums.h"

class Hero;
class Dungeon;

class Item{
    private:
        type_item item_type;
    public:
        Item(type_item T) noexcept: item_type(T) {}

        virtual ~Item() = default;

        type_item getItem_Type() const noexcept { return item_type; }
        void setType(type_item T) noexcept { item_type = T; }

        Item& operator =(const Item& I) noexcept;

        virtual void use(Dungeon &Dungeon) = 0;


};

#endif // ITEM_H
