#ifndef WEAPONENCHANTMENT_H
#define WEAPONENCHANTMENT_H
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
        WeaponEnchantment() noexcept: Weapon(), Enchantment() { setType(type_item::weapon_enchantment); }
        /*!
         * @brief Конструктор по значению
         * @param N Название оружия
         */
        WeaponEnchantment(name_weapon N) noexcept: Weapon(N), Enchantment() { setType(type_item::weapon_enchantment); }
        /*!
         * @brief Конструктор по значению
         * @param N Название оружия
         * @param T Тип зачарования
         */
        WeaponEnchantment(name_weapon N, type_enchantment T) noexcept: Weapon(N), Enchantment(T) { setType(type_item::weapon_enchantment); }

        /*!
         * @brief Виртуальный метод получения урона, наносимого оружием врагу
         * @param enemy Враг
         * @return Итоговый урон
         */
        int getDamage(Enemy *enemy) const noexcept override;
        /*!
         * @brief Виртуальнйы метод - взять оружие в руки
         * @param Карта
         */
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}
};

#endif // WEAPONENCHANTMENT_H
