#include "bunch.h"
#include "hero.h"

Bunch::Bunch(type_bunch T): Item(type_item::bunch){
    try{
        bunch_type = T;
        count = SetCount::createCount(T);
    } catch(...){
        throw;
    }
}

Bunch& Bunch::operator= (const Bunch &I) noexcept{
    if (this != &I){
        bunch_type = I.bunch_type;
        count = I.count;

        Item::operator=(I);
    }
}

Item* Bunch::take(Hero *H){
    if (bunch_type == type_bunch::small){
        H->setC_Bunch(H->getC_Bunch() + 5);
    } else if (bunch_type == type_bunch::medium){
        H->setC_Bunch(H->getC_Bunch() + 10);
    } else {
        H->setC_Bunch(H->getC_Bunch() + 15);
    }
    return nullptr;
}
