#include "weaponartifact.h"
#include "hero.h"

WeaponArtifact::WeaponArtifact(name_weapon N, type_artifact T): Weapon(N), Artifact(T){
    bonus_damage = SetDamage::setBonus_Damage(T);
    setType(type_item::weapon_artifact);
}

WeaponArtifact& WeaponArtifact::operator=(const WeaponArtifact& I) noexcept{
    if (this != &I){
        bonus_damage = I.bonus_damage;
        Artifact::operator=(I);
        Weapon::operator=(I);
    }
    return *this;
}

int WeaponArtifact::getDamage(Enemy *enemy) const noexcept{
    return rand() % (getMax_Damage() - getMin_Damage()) + bonus_damage;
}

Item* WeaponArtifact::take(Hero *H){
    Item *tmp = H->getWeapon();
    H->setWeapon(this);
    return tmp;
}
