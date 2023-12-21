#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "../item.h"
#include "../../upgrades/artifact/artifact.h"
/*!
 * @brief Класс брони
 */
class Equipment: public Item{
    protected:
        std::string item_type;
        // Название брони
        std::string equipment_name;
        // Тип брони
        std::string equipment_type;
        // Минимальная защита
        int min_protect;
        // Максимальная защита
        int max_protect;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Equipment() noexcept: min_protect(0), max_protect(0), item_type("equipment") {}
        Equipment(std::string en, std::string et, int mn, int mx) noexcept: equipment_name(en),
            equipment_type(et), min_protect(mn), max_protect(mx), item_type("equipment") {}
        /*!
         * @brief Конструктор по значению
         * @param N Имя брони
         * @param T Тип брони
         */

        std::string getEquipment_Name() const noexcept { return equipment_name; }
        /*!
         * @brief Геттер типа брони
         * @return Тип брони
         */
        std::string getEquipment_Type() const noexcept { return equipment_type; }
        /*!
         * @brief Геттер минимальной защиты
         * @return Минимальная защита
         */
        int getMin_Protect() const noexcept { return min_protect; }
        /*!
         * @brief Геттер максимальной защиты
         * @return Максиамльная защита
         */
        int getMax_Protect() const noexcept { return max_protect; }

        /*!
         * @brief Оператор копирования
         * @param I Другая броня
         * @return Ссылка на текущую броню
         */
        Equipment& operator=(const Equipment& I) noexcept;

        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return equipment_name + "_" + equipment_type; }
        int getValue() const noexcept override;
        void use(Dungeon &dungeon) override;
        Item* buildItem(const json& data) override;

};
extern "C" Item* load_equipment();
#endif // EQUIPMENT_H
