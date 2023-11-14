#ifndef WEAPONARTIFACT_H
#define WEAPONARTIFACT_H
#include "weapon.h"
#include "artifact.h"
class WeaponArtifact: public virtual Weapon, public Artifact{
    protected:
        int bonus_damage;
    public:
        WeaponArtifact(): Artifact(), Weapon(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        WeaponArtifact(name_weapon N): Weapon(N), Artifact(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        WeaponArtifact(name_weapon N, type_artifact T);

        WeaponArtifact& operator=(const WeaponArtifact& I) noexcept;

        int getDamage(Enemy *enemy) const noexcept override;

        Item* take(Hero *H) override;

};

#endif // WEAPONARTIFACT_H
