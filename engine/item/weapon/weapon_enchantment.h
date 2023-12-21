#ifndef WEAPON_ENCHANTMENT_H
#define WEAPON_ENCHANTMENT_H

#include "weapon.h"
#include "../../upgrades/enchantment/enchantment.h"

/*!
 * @brief Класс зачарованного оружия
 */

class WeaponEnchantment: public virtual Weapon, public Enchantment{
    public:
        /*!
         * @brief Пустой конструктор
         */
        WeaponEnchantment() noexcept: Weapon(), Enchantment() { item_type = "weapon_enchantment"; }
        WeaponEnchantment(std::string wn, int mn, int mx, std::string et, std::list<std::pair<std::string, double>> c) noexcept:
            Weapon(wn, mn, mx), Enchantment(et, c) { item_type = "weapon_enchantment"; }

        /*!
         * @brief Виртуальнйы метод - взять оружие в руки
         * @param Карта
         */
        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return weapon_name; }
        int getValue() const noexcept override;
        void use(Dungeon &dungeon) override;
        Item* buildItem(const json& data) override;
};
extern "C" Item* load_weapon_enchantment();
#endif // WEAPONENCHANTMENT_H
