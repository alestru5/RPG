#include "potion.h"

void Potion::use(Dungeon &dungeon){
    dungeon.getHero().getTable().setValue(changes.first, dungeon.getHero().getTable().getValue(changes.first) + changes.second);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
    dungeon.getHero().setInventory(I);
}

Potion& Potion::operator =(const Potion &I) noexcept{
    if (this != &I){
        item_type = I.item_type;
        potion_name = I.potion_name; 
        changes = I.changes;
    }
    return *this;
}

Item& Potion::buildItem(const json& data) {
    item_type = data.at("item_type").get<std::string>();
    potion_name = data.at("item_name").get<std::string>();
    changes = std::make_pair("experience", 100);
    return *this;
}
