#include "item.h"

Item& Item::operator =(const Item& I) noexcept{
    if (this != &I){
        item_type = I.item_type;
    }
    return *this;
}
