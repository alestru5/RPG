#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

#include "item.h"
#include "setdamage.h"
#include "enums.h"
#include "enemy.h"
/*!
 * @brief Класс оружия
 */
class Weapon: public Item{
    private:
        // Название оружия
        name_weapon weapon_name;
        // Минимальный урон
        int min_damage;
        // Максимальный урон
        int max_damage;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Weapon() noexcept: min_damage(0), max_damage(0), weapon_name(name_weapon::knife), Item(type_item::weapon) {}
        /*!
         * @brief Конструктор по значению
         * @param n Название оружия
         */
        explicit Weapon(name_weapon n) noexcept;

        /*!
         * @brief Геттер названия оружия
         * @return Название оружия
         */
        name_weapon getWeapon_Name() const noexcept { return weapon_name; }
        /*!
         * @brief Геттер минимального урона
         * @return Минимальный урон
         */
        int getMin_Damage() const noexcept {return min_damage; }
        /*!
         * @brief Геттер максимального урона
         * @return МАксимальный урон
         */
        int getMax_Damage() const noexcept {return max_damage; }

        /*!
         * @brief Сеттер названия оружия
         * @param t Название оружия
         * @return Ссылка на текущее оружие
         */
        Weapon& setName(name_weapon t) noexcept;
        /*!
         * @brief Оператор копирования
         * @param I Другое оружие
         * @return Ссылка на текущее оружие
         */
        Weapon& operator=(const Weapon& I) noexcept;
        /*!
         * @brief Виртуальный метод получения урона, наносимого оружием врагу
         * @param enemy Враг
         * @return Итоговый урон
         */
        virtual int getDamage(Enemy *enemy) const noexcept;
        /*!
         * @brief Виртуальнйы метод - взять оружие в руки
         * @param Карта
         */
        void use(Dungeon &dungeon) override;
};

#endif // WEAPON_H
