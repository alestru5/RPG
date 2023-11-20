#include "setdamage.h"
#include "weapon.h"

std::pair<int, int> SetDamage::createDamage(name_weapon n){
    if (n == name_weapon::knife){
        return std::make_pair(1, 10);
    } else if (n == name_weapon::nunchucks){
        return std::make_pair(10, 20);
    } else if (n == name_weapon::sword){
        return std::make_pair(20, 50);
    }
    return std::make_pair(11, 13);
}

int SetDamage::setBonus_Damage(type_artifact T){
    if (T == type_artifact::casual){
        return 5;
    } else if (T == type_artifact::rare){
        return 10;
    } else if (T == type_artifact::mythical){
        return 15;
    } else if (T == type_artifact::legendary){
        return 25;
    }
    return 0;
}

std::pair<int, int> SetDamage::createDamage(name_enemy n){
    if (n == name_enemy::black_druid){
        return std::make_pair(8, 9);
    } else if(n == name_enemy::blue_wolf){
        return std::make_pair(10, 11);
    } else if (n == name_enemy::red_tiger){
        return std::make_pair(9, 11);
    } else if (n == name_enemy::white_golem){
        return std::make_pair(11, 13);
    }
    return std::make_pair(0, 0);
}
