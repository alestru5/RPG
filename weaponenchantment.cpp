#include "weaponenchantment.h"

WeaponEnchantment& WeaponEnchantment::operator=(const WeaponEnchantment& I) noexcept{
    if (this != &I){
        Enchantment::operator=(I);
    }
    return *this;
}
