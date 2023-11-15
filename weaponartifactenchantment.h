#ifndef WEAPONARTIFACTENCHANTMENT_H
#define WEAPONARTIFACTENCHANTMENT_H
#include "weaponartifact.h"
#include "weaponenchantment.h"

class WeaponArtifactEnchantment: public WeaponArtifact, public WeaponEnchantment{
    public:
        WeaponArtifactEnchantment():
            WeaponArtifact(), WeaponEnchantment(), Weapon(){ setType(type_item::weapon_artifact_enchantment); }
        WeaponArtifactEnchantment(name_weapon N, type_artifact A, type_enchantment E):
            WeaponArtifact(N, A), WeaponEnchantment(N, E), Weapon(N){ setType(type_item::weapon_artifact_enchantment); }

        ~WeaponArtifactEnchantment() {}

        int getDamage(Enemy *enemy) const noexcept override;

        void use(Dungeon &dungeon) override;

};

#endif // WEAPONARTIFACTENCHANTMENT_H
