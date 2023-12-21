#include "bunch.h"

Bunch& Bunch::operator= (const Bunch &I) noexcept{
    if (this != &I){
        item_type = I.item_type;
        bunch_name = I.bunch_name;
        count = I.count;
    }
    return *this;
}

void Bunch::use(Dungeon &dungeon){
    name_potion t = name_potion::agility;
    dungeon.getHero().setC_Bunch(dungeon.getHero().getC_Bunch() + count);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
    dungeon.getHero().setInventory(I);
}

Item& Bunch::buildItem(const json& data) {
    item_type = data.at("item_type").get<std::string>();
    bunch_name = data.at("item_name").get<std::string>();
    count = data.at("count").get<int>();
    return *this;
}
