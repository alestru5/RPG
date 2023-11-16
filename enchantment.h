#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <list>

#include "enums.h"
#include "enemy.h"

class Enchantment{
    private:
        type_enchantment enchantment_type;
        std::list<std::pair<trait, double>> coef;

    public:
        Enchantment() noexcept;
        Enchantment(type_enchantment T) noexcept;

        ~Enchantment() {}

        type_enchantment getEnchantment_Type() const noexcept { return enchantment_type; }
        std::list<std::pair<trait, double>> getCoef() const noexcept { return coef; }

        void setEnchantment_Type(type_enchantment T) noexcept;

        double getMultiply(Enemy *enemy) const noexcept;

        Enchantment& operator=(const Enchantment& I) noexcept;

};

#endif // ENCHANTMENT_H
