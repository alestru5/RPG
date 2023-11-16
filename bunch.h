#ifndef BUNCH_H
#define BUNCH_H

#include <iostream>

#include "item.h"
#include "enums.h"
#include "setcount.h"

class Bunch: public Item{
    private:
        type_bunch bunch_type;
        int count;

    public:
        Bunch() noexcept: count(0), Item(type_item::bunch) {}
        Bunch(type_bunch T) noexcept;

        type_bunch getBunch_Type() const noexcept { return bunch_type; }
        int getCount() const noexcept { return count; }

        Bunch &operator= (const Bunch &I) noexcept;

        void use(Dungeon &dungeon) override;

};

#endif // BUNCH_H
