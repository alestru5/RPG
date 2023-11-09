#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>

#include "item.h"
#include "setdamage.h"

#include "enums.h"


class Weapon: public Item{
    private:
        name_weapon weapon_name;
        int min_damage;
        int max_damage;
    public:
        Weapon() noexcept: min_damage(0), max_damage(0), weapon_name(name_weapon::knife), Item(type_item::weapon) {}
        explicit Weapon(name_weapon n) noexcept;

        name_weapon getWeapon_Name() const noexcept { return weapon_name; }
        int getMin_Damage() const noexcept {return min_damage; }
        int getMax_Damage() const noexcept {return max_damage; }

        Weapon& setName(name_weapon t) noexcept;
        Weapon& operator=(const Weapon& I) noexcept;

        Item* take(Hero *H) override;



};

#endif // WEAPON_H
