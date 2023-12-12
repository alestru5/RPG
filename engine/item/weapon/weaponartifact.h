#ifndef WEAPONARTIFACT_H
#define WEAPONARTIFACT_H
#include "weapon.h"
#include "../../upgrades/artifact/artifact.h"
/*!
 * @brief Класс оружия-артифакта
 */
class WeaponArtifact: public virtual Weapon, public Artifact{
    protected:
        int bonus_damage;
    public:
        /*!
         * @brief Пустой конструктор
         */
        WeaponArtifact() noexcept: Artifact(), Weapon(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        /*!
         * @brief Конструктор по значению
         * @param N Название оружия
         */
        WeaponArtifact(name_weapon N) noexcept: Weapon(N), Artifact(), bonus_damage(0) { setType(type_item::weapon_artifact); }
        /*!
         * @brief Конструктор по значению
         * @param N Название оружия
         * @param T Тип артефакта
         */
        WeaponArtifact(name_weapon N, type_artifact T) noexcept;

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

#endif // WEAPONARTIFACT_H
