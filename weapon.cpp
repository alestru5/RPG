#include "weapon.h"
#include "game.h"
#include "setdamage.h"

Weapon::Weapon(name_weapon n) noexcept: Item(type_item::weapon) {
    try{
        min_damage = SetDamage::createDamage(n).first;
        max_damage = SetDamage::createDamage(n).second;
        weapon_name = n;
    } catch(...){
        throw;
    }
}

Weapon& Weapon::setName(name_weapon n) noexcept{
    try{
        min_damage = SetDamage::createDamage(n).first;
        max_damage = SetDamage::createDamage(n).second;
        weapon_name = n;
        return *this;
    } catch(...){
        throw;
    }
}

Weapon& Weapon::operator=(const Weapon& I) noexcept{
    if (this != &I){
        weapon_name = I.weapon_name;
        min_damage = I.min_damage;
        max_damage = I.max_damage;

        Item::operator=(I);
    }
    return *this;
}

int Weapon::getDamage(Enemy *enemy) const noexcept{
    return rand() % (max_damage - min_damage) + min_damage;
}

Item* Weapon::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    return tmp;
}
