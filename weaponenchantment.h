#ifndef WEAPONENCHANTMENT_H
#define WEAPONENCHANTMENT_H
#include "weapon.h"
#include "enchantment.h"

class WeaponEnchantment: public virtual Weapon, public Enchantment{
    public:
        WeaponEnchantment(): Weapon(), Enchantment() { setType(type_item::weapon_enchantment); }
        WeaponEnchantment(name_weapon N): Weapon(N), Enchantment() { setType(type_item::weapon_enchantment); }
        WeaponEnchantment(name_weapon N, type_enchantment T): Weapon(N), Enchantment(T) { setType(type_item::weapon_enchantment); }

        WeaponEnchantment& operator=(const WeaponEnchantment& I) noexcept;
};

#endif // WEAPONENCHANTMENT_H
