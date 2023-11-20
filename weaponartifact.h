#ifndef WEAPONARTIFACT_H
#define WEAPONARTIFACT_H
#include "weapon.h"
#include "artifact.h"
class WeaponArtifact: public virtual Weapon, public Artifact{
    protected:
        int bonus_damage;
    public:
        WeaponArtifact() noexcept: Artifact(), Weapon(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        WeaponArtifact(name_weapon N) noexcept: Weapon(N), Artifact(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        WeaponArtifact(name_weapon N, type_artifact T) noexcept;

        ~WeaponArtifact() {}

        int getDamage(Enemy *enemy) const noexcept override;

        void use(Dungeon &dungeon) override;

};

#endif // WEAPONARTIFACT_H
