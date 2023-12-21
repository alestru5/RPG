#include "enchantment.h"

double Enchantment::getMultiply() const noexcept{
    /*if (!enemy){
        return 1.;
    }
    for (auto iter = coef.begin(); iter != coef.end(); iter++){
        if ((*iter).first == "black" && enemy->getName() == name_enemy::black_druid){
            return (*iter).second;
        }
        if ((*iter).first == "blue" && enemy->getName() == name_enemy::blue_wolf){
            return (*iter).second;
        }
        if ((*iter).first == "red" && enemy->getName() == name_enemy::red_tiger){
            return (*iter).second;
        }
        if ((*iter).first == "white" && enemy->getName() == name_enemy::white_golem){
            return (*iter).second;
        }
    }*/
    return 1.;

}

void Enchantment::setAllC(std::string et, double c) noexcept{
    enchantment_type = et;
    coef.push_back(std::make_pair(et, c));
}

Enchantment& Enchantment::operator=(const Enchantment& I) noexcept{
    if (this != &I){
        enchantment_type = I.enchantment_type;
        coef = I.coef;
    }
    return *this;
}
