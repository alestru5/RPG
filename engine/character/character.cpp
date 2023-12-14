#include "character.h"
#include "../game.h"
#include "../dungeon/cell/cell.h"
#include "../dungeon/dungeon.h"

void Character::setY(int j){
    if (j < 0){
        throw std::invalid_argument("invalid coord");
    }
    y = j;
}

void Character::setX(int i){
    if (i < 0){
        throw std::invalid_argument("invalid coord");
    }
    x = i;
}

void Character::setMax_Hp(int hp){
    if (hp <= 0){
        throw std::invalid_argument("not positive hp");
    }
    max_hp = hp;
}

void Character::setCur_Hp(int hp){
    if (hp < 0){
        throw std::invalid_argument("negative hp");
    }
    if (hp > max_hp){
        throw std::invalid_argument("bigger than max_hp");
    }
    cur_hp = hp;
}
