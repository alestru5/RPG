#include "setcoef.h"

std::list<std::pair<trait, double>> SetCoef::createCoef(type_enchantment T){
    std::list<std::pair<trait, double>> coef;
    if (T == type_enchantment::BlackKiller){
        coef.push_back(std::make_pair(trait::black, 2));
        coef.push_back(std::make_pair(trait::blue, 1.5));
        coef.push_back(std::make_pair(trait::white, 0.5));
        coef.push_back(std::make_pair(trait::red, 1));
    } else if (T == type_enchantment::BlueKiller){
        coef.push_back(std::make_pair(trait::black, 1.5));
        coef.push_back(std::make_pair(trait::blue, 2));
        coef.push_back(std::make_pair(trait::white, 0.5));
        coef.push_back(std::make_pair(trait::red, 1));
    } else if (T == type_enchantment::RedKiller){
        coef.push_back(std::make_pair(trait::black, 1.5));
        coef.push_back(std::make_pair(trait::blue, 1));
        coef.push_back(std::make_pair(trait::white, 0.5));
        coef.push_back(std::make_pair(trait::red, 2));
    } else if (T == type_enchantment::WhiteKiller){
        coef.push_back(std::make_pair(trait::black, 1));
        coef.push_back(std::make_pair(trait::blue, 1.5));
        coef.push_back(std::make_pair(trait::white, 2));
        coef.push_back(std::make_pair(trait::red, 0.5));
    } else{
        throw std::invalid_argument("Its not enchantment");
    }
}
