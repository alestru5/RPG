#ifndef WEAPONENCHANTMENT_H
#define WEAPONENCHANTMENT_H
#include "weapon.h"
#include "enchantment.h"

class WeaponEnchantment: public virtual Weapon, public Enchantment{
    public:
        WeaponEnchantment() noexcept: Weapon(), Enchantment() { setType(type_item::weapon_enchantment); }
        WeaponEnchantment(name_weapon N) noexcept: Weapon(N), Enchantment() { setType(type_item::weapon_enchantment); }
        WeaponEnchantment(name_weapon N, type_enchantment T) noexcept: Weapon(N), Enchantment(T) { setType(type_item::weapon_enchantment); }

        ~WeaponEnchantment() {}

        int getDamage(Enemy *enemy) const noexcept override;

        void use(Dungeon &dungeon) override;
};

#endif // WEAPONENCHANTMENT_H
