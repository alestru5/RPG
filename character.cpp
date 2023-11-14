#include "character.h"
#include "game.h"
#include "cell.h"
#include "dungeon.h"

Character::Character(int e, int m, int c, int x, int y){
    if (e < 0 || m < 0 || c < 0 || c > m || x < 0 || y < 0){
        throw std::invalid_argument("negative argiments");
    }
    experience = e;
    max_hp = m;
    cur_hp = c;
    this->x = x;
    this->y = y;
}


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

void Character::setExperience(int exp){
    if (exp <= 0){
        std::invalid_argument("not positive experiece");
    }
    experience = exp;
}

void Character::setMax_Hp(int hp){
    if (hp <= 0){
        std::invalid_argument("not positive hp");
    }
    max_hp = hp;
}

void Character::setCur_Hp(int hp){
    if (hp <= 0){
        std::invalid_argument("not positive hp");
    }
    cur_hp = std::min(hp, max_hp);
}
