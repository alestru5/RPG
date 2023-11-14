#include "weaponartifactenchantment.h"
#include "hero.h"

int WeaponArtifactEnchantment::getDamage(Enemy *enemy) const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())) * getMultiply(enemy)) + bonus_damage;
}

Item* WeaponArtifactEnchantment::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    if (tmp != nullptr && (tmp->getItem_Type() == type_item::weapon_artifact || tmp->getItem_Type() == type_item::weapon_artifact_enchantment)){
        if (tmp->getItem_Type() == type_item::weapon_artifact){
            dynamic_cast<WeaponArtifact *>(tmp)->unUseChanges(H);
        } else{
            dynamic_cast<WeaponArtifactEnchantment *>(tmp)->unUseChanges(H);
        }
    }
    useChanges(H);
    return tmp;
}
