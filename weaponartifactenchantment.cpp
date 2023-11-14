#include "weaponartifactenchantment.h"
#include "hero.h"

int WeaponArtifactEnchantment::getDamage(Enemy *enemy) const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())) * getMultiply(enemy)) + bonus_damage;
}

Item* WeaponArtifactEnchantment::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    return tmp;
}
