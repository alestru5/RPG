#include "potion.h"
#include "../../dungeon/dungeon.h"

void Potion::use(Dungeon &dungeon){
    dungeon.getHero().getTable().setValue(changes.first, dungeon.getHero().getTable().getValue(changes.first) + changes.second);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
    dungeon.getHero().setInventory(I);
}

Potion& Potion::operator =(const Potion &I) noexcept{
    if (this != &I){
        potion_name = I.potion_name;
        item_type = I.item_type;
        changes = I.changes;
    }
    return *this;
}

