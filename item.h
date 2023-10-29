#ifndef ITEM_H
#define ITEM_H

#include "enums.h"

class Item{
    private:
        type_item item_type;
    public:
        Item(type_item T): item_type(T) {}

        type_item getItem_Type() const noexcept { return item_type; }
        void setType(type_item T) { item_type = T; }

        Item& operator =(const Item& I) noexcept;


};

#endif // ITEM_H
