#include "bunch.h"
#include "../../character/hero/hero.h"
#include "../../dungeon/dungeon.h"

Bunch& Bunch::operator= (const Bunch &I) noexcept{
    if (this != &I){
        item_type = I.item_type;
        bunch_name = I.bunch_name;
        count = I.count;
    }
    return *this;
}

void Bunch::use(Dungeon &dungeon){
    dungeon.getHero().setC_Bunch(dungeon.getHero().getC_Bunch() + count);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
    dungeon.getHero().setInventory(I);
}
