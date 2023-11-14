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

double Enchantment::getMultiply(Enemy *enemy) const noexcept{
    if (!enemy){
        return 1.;
    }
    if (enemy->getName() == name_enemy::black_druid){
        for (auto iter = coef.begin(); iter != coef.end(); iter++){
            if ((*iter).first == trait::black){
                return (*iter).second;
            }
        }
    } else if (enemy->getName() == name_enemy::blue_wolf){
        for (auto iter = coef.begin(); iter != coef.end(); iter++){
            if ((*iter).first == trait::blue){
                return (*iter).second;
            }
        }
    } else if (enemy->getName() == name_enemy::red_tiger){
        for (auto iter = coef.begin(); iter != coef.end(); iter++){
            if ((*iter).first == trait::red){
                return (*iter).second;
            }
        }
    } else if (enemy->getName() == name_enemy::white_golem){
        for (auto iter = coef.begin(); iter != coef.end(); iter++){
            if ((*iter).first == trait::white){
                return (*iter).second;
            }
        }
    }
    return 1.;

}

Enchantment& Enchantment::operator=(const Enchantment& I) noexcept{
    if (this != &I){
        enchantment_type = I.enchantment_type;
        coef = I.coef;
    }
    return *this;
}
