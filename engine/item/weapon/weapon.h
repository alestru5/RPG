#ifndef WEAPON_H
#define WEAPON_H

#include "../item.h"
#include "../../upgrades/artifact/artifact.h"
/*!
 * @brief Класс оружия
 */
class Weapon: public Item{
    protected:
        // Название оружия
        std::string item_type;
        std::string weapon_name;
        // Минимальный урон
        int min_damage;
        // Максимальный урон
        int max_damage;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Weapon() noexcept: min_damage(0), max_damage(0), item_type("weapon"){}
        Weapon(std::string wn, int mn, int mx) noexcept: weapon_name(wn), min_damage(mn), max_damage(mx), item_type("weapon") {}
        /*!
         * @brief Геттер названия оружия
         * @return Название оружия
         */
        std::string getWeapon_Name() const noexcept { return weapon_name; }
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
         * @brief Оператор копирования
         * @param I Другое оружие
         * @return Ссылка на текущее оружие
         */
        Weapon& operator=(const Weapon& I) noexcept;
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

extern "C" const Item& load_weapon();
#endif // WEAPON_H
