#include "potion.h"
#include "hero.h"
Potion::Potion(name_potion N) noexcept: Item(type_item::potion){
    try{
        potion_name = N;
        changes = SetPotion::createChanges(N);
    } catch(...){
        throw;
    }
}

void Potion::drink(Hero &hero){
    if (changes.first == changes_characteristic::agility){
        hero.getTable().setValue(short_characteristic::a, hero.getTable().getValue(short_characteristic::a) + changes.second);
    } else if (changes.first == changes_characteristic::experience){
        hero.setExperience(hero.getExperience() + changes.second);
    } else if (changes.first == changes_characteristic::hp){
        hero.setCur_Hp(hero.getCur_Hp() + changes.second);
    } else if (changes.first == changes_characteristic::intelligence){
        hero.getTable().setValue(short_characteristic::i, hero.getTable().getValue(short_characteristic::i) + changes.second);
    } else if (changes.first == changes_characteristic::strength){
        hero.getTable().setValue(short_characteristic::s, hero.getTable().getValue(short_characteristic::s) + changes.second);
    } else if (changes.first == changes_characteristic::endurance){
        hero.getTable().setValue(short_characteristic::e, hero.getTable().getValue(short_characteristic::e) + changes.second);
    }
}

Potion& Potion::operator =(const Potion &I) noexcept{
    if (this != &I){
        potion_name = I.potion_name;
        changes = I.changes;
        Item::operator=(I);
    }
    return *this;
}

Item* Potion::take(Hero *H){

    return this;
}
