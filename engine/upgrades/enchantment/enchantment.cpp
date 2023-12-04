#include "enchantment.h"
#include "../../helps/sets/setcoef.h"

Enchantment::Enchantment() noexcept{
    enchantment_type = type_enchantment::BlackKiller;
    coef = SetCoef::createCoef(type_enchantment::BlackKiller);
}

Enchantment::Enchantment(type_enchantment T) noexcept{
    enchantment_type = T;
    coef = SetCoef::createCoef(T);
}

void Enchantment::setEnchantment_Type(type_enchantment T) noexcept{
    enchantment_type = T;
    coef = SetCoef::createCoef(T);
}

double Enchantment::getMultiply(Enemy *enemy) const noexcept{
    if (!enemy){
        return 1.;
    }
    for (auto iter = coef.begin(); iter != coef.end(); iter++){
        if ((*iter).first == trait::black && enemy->getName() == name_enemy::black_druid){
            return (*iter).second;
        }
        if ((*iter).first == trait::blue && enemy->getName() == name_enemy::blue_wolf){
            return (*iter).second;
        }
        if ((*iter).first == trait::red && enemy->getName() == name_enemy::red_tiger){
            return (*iter).second;
        }
        if ((*iter).first == trait::white && enemy->getName() == name_enemy::white_golem){
            return (*iter).second;
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
