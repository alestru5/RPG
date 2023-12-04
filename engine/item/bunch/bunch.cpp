#include "bunch.h"
#include "../../character/hero/hero.h"
#include "../../dungeon/dungeon.h"

Bunch::Bunch(type_bunch T) noexcept: Item(type_item::bunch){
    bunch_type = T;
    count = SetCount::createCount(T);
}

Bunch& Bunch::operator= (const Bunch &I) noexcept{
    if (this != &I){
        bunch_type = I.bunch_type;
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
