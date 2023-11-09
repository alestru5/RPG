#include "weaponenchantment.h"
#include "hero.h"

WeaponEnchantment& WeaponEnchantment::operator=(const WeaponEnchantment& I) noexcept{
    if (this != &I){
        Enchantment::operator=(I);
    }
    return *this;
}

Item* WeaponEnchantment::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    return tmp;
}
