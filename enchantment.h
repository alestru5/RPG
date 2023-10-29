#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <list>
#include "enums.h"



class Enchantment{
    private:
        type_enchantment enchantment_type;
        std::list<std::pair<trait, double>> coef;
    public:
        Enchantment();
        Enchantment(type_enchantment T);
        type_enchantment getEnchantment_Type() const noexcept { return enchantment_type; }
        std::list<std::pair<trait, double>> getCoef() const noexcept { return coef; }

        void setEnchantment_Type(type_enchantment T) noexcept;

        Enchantment& operator=(const Enchantment& I) noexcept;

};

#endif // ENCHANTMENT_H