#include "weaponartifactenchantment.h"
#include "hero.h"

Item* WeaponArtifactEnchantment::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    return tmp;
}
