#include "enemy.h"
#include "setitem.h"
Enemy::Enemy(): Character(), name(name_enemy::white_golem){
    min_damage = SetDamage::createDamage(name_enemy::white_golem).first;
    max_damage = SetDamage::createDamage(name_enemy::white_golem).second;
    item = SetItem::createItem();
}
Enemy::Enemy(int i, int j): Enemy(){
    x = i;
    y = j;
}


/*int Enemy::take_damage(Character *C) const noexcept{
    int damage = min_damage + rand() % (max_damage - min_damage);
    return damage;
}

bool Enemy::get_damage(int damage){
    cur_hp -= damage;
    if (cur_hp <= 0){
        return false;
    }
    return true;
}*/

