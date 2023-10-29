#ifndef POTION_H
#define POTION_H

#include <list>
#include "table.h"
#include "item.h"
#include "enums.h"
#include "setpotion.h"

class Potion: public Item{
    private:
        name_potion potion_name;
        std::pair<changes_characteristic, int> changes;
    public:
        Potion() noexcept: changes(), Item(type_item::potion){}
        Potion(name_potion N) noexcept;

        name_potion getPotion_Name() const noexcept { return potion_name; }
        std::pair<changes_characteristic, int> getChanges() { return changes; }

        Potion &operator =(const Potion &I) noexcept;
};

#endif // POTION_H
