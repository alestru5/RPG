#include "enchantment.h"
#include "setcoef.h"

Enchantment::Enchantment(){
    try{
        enchantment_type = type_enchantment::BlackKiller;
        coef = SetCoef::createCoef(type_enchantment::BlackKiller);
    } catch(...){
        throw;
    }
}

Enchantment::Enchantment(type_enchantment T){
    try{
        enchantment_type = T;
        coef = SetCoef::createCoef(T);
    } catch(...){
        throw;
    }
}

void Enchantment::setEnchantment_Type(type_enchantment T) noexcept{
    try{
        enchantment_type = T;
        coef = SetCoef::createCoef(T);
    } catch(...){
        throw;
    }
}

Enchantment& Enchantment::operator=(const Enchantment& I) noexcept{
    if (this != &I){
        enchantment_type = I.enchantment_type;
        coef = I.coef;
    }
    return *this;
}
