#include "potion.h"
#include "hero.h"
#include "dungeon.h"

Potion::Potion(name_potion N) noexcept: Item(type_item::potion){
    potion_name = N;
    changes = SetPotion::createChanges(N);
}

void Potion::use(Dungeon &dungeon){
    if (changes.first == changes_characteristic::agility){
        dungeon.getHero().getTable().setValue(short_characteristic::a, dungeon.getHero().getTable().getValue(short_characteristic::a) + changes.second);
    } else if (changes.first == changes_characteristic::experience){
        dungeon.getHero().setExperience(dungeon.getHero().getExperience() + changes.second);
    } else if (changes.first == changes_characteristic::hp){
        dungeon.getHero().setCur_Hp(std::min(dungeon.getHero().getCur_Hp() + changes.second, dungeon.getHero().getMax_Hp()));
    } else if (changes.first == changes_characteristic::intelligence){
        dungeon.getHero().getTable().setValue(short_characteristic::i, dungeon.getHero().getTable().getValue(short_characteristic::i) + changes.second);
    } else if (changes.first == changes_characteristic::strength){
        dungeon.getHero().getTable().setValue(short_characteristic::s, dungeon.getHero().getTable().getValue(short_characteristic::s) + changes.second);
    } else if (changes.first == changes_characteristic::endurance){
        dungeon.getHero().getTable().setValue(short_characteristic::e, dungeon.getHero().getTable().getValue(short_characteristic::e) + changes.second);
    }
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
    dungeon.getHero().setInventory(I);
}

Potion& Potion::operator =(const Potion &I) noexcept{
    if (this != &I){
        potion_name = I.potion_name;
        changes = I.changes;
        Item::operator=(I);
    }
    return *this;
}

