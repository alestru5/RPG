#include "bunch.h"

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
