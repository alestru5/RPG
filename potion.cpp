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

Potion& Potion::operator =(const Potion &I) noexcept{
    if (this != &I){
        potion_name = I.potion_name;
        changes = I.changes;

        Item::operator=(I);
    }
    return *this;
}

Item* Potion::take(Hero *H){
    if (H->getPotion().size() < H->getM_Potion()){
        std::list<Potion *> tmp = H->getPotion();
        tmp.push_back(this);
        H->setPotion(tmp);
        return nullptr;
    }
    return this;
}
