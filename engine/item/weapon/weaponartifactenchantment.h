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
            WeaponArtifact(), WeaponEnchantment(), Weapon(){ setType(type_item::weapon_artifact_enchantment); }
        /*!
         * @brief Конструктор по значению
         * @param N Название оружия
         * @param A Тип артифакта
         * @param E Тип зачарования
         */
        WeaponArtifactEnchantment(name_weapon N, type_artifact A, type_enchantment E) noexcept:
            WeaponArtifact(N, A), WeaponEnchantment(N, E), Weapon(N){ setType(type_item::weapon_artifact_enchantment); }
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

#endif // WEAPONARTIFACTENCHANTMENT_H
