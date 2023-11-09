#ifndef ITEM_H
#define ITEM_H

#include "enums.h"

class Hero;

class Item{
    private:
        type_item item_type;
    public:
        Item(type_item T): item_type(T) {}

        ~Item() {}

        type_item getItem_Type() const noexcept { return item_type; }
        void setType(type_item T) { item_type = T; }

        Item& operator =(const Item& I) noexcept;

        virtual Item* take(Hero *H) = 0;


};

#endif // ITEM_H
