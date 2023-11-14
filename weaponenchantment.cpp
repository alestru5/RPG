#include "weaponenchantment.h"
#include "hero.h"
#include "weaponartifactenchantment.h"
WeaponEnchantment& WeaponEnchantment::operator=(const WeaponEnchantment& I) noexcept{
    if (this != &I){
        Enchantment::operator=(I);
    }
    return *this;
}

int WeaponEnchantment::getDamage(Enemy *enemy) const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())) * getMultiply(enemy));
}

Item* WeaponEnchantment::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    if (tmp != nullptr){
        if (tmp->getItem_Type() == type_item::weapon_artifact){
            dynamic_cast<WeaponArtifact *>(tmp)->unUseChanges(H);
        }
        if (tmp->getItem_Type() == type_item::weapon_artifact_enchantment){
            dynamic_cast<WeaponArtifactEnchantment *>(tmp)->unUseChanges(H);
        }
    }
    return tmp;
}
