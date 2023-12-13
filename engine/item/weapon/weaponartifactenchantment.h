#ifndef WEAPONARTIFACTENCHANTMENT_H
#define WEAPONARTIFACTENCHANTMENT_H

#include "weaponartifact.h"
#include "weaponenchantment.h"
/*!
 * @brief Класс зачарованного оружия-артефакта
 */
class WeaponArtifactEnchantment: public WeaponArtifact, public WeaponEnchantment{
    public:
        /*!
         * @brief Пустой конструктор
         */
        WeaponArtifactEnchantment() noexcept:
            WeaponArtifact(), WeaponEnchantment(), Weapon(){ item_type = "weapon_artifact_enchantment"; }

        WeaponArtifactEnchantment(std::string wn, int mn, int mx, int bd, std::string at, std::list<std::pair<std::string, int>> co,
                                  std::string et, std::list<std::pair<std::string, double>> c) noexcept: Weapon(wn, mn, mx),
            WeaponArtifact(wn, mn, mx, bd, at, co), WeaponEnchantment(wn, mn, mx, et, c) {}
        /*!
         * @brief Виртуальнйы метод - взять оружие в руки
         * @param Карта
         */
        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return weapon_name; }
        int getValue() const noexcept override;
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}

};

#endif // WEAPONARTIFACTENCHANTMENT_H
