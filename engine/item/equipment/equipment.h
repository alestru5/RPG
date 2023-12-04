#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "../item.h"
#include "../../upgrades/artifact/artifact.h"
#include "../../helps/sets/setprotect.h"
/*!
 * @brief Класс брони
 */
class Equipment: public Item{
    protected:
        // Название брони
        name_equipment equipment_name;
        // Тип брони
        type_equipment equipment_type;
        // Минимальная защита
        int min_protect;
        // Максимальная защита
        int max_protect;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Equipment() noexcept: min_protect(0), max_protect(0), Item(type_item::equipment) {}
        /*!
         * @brief Конструктор по значению
         * @param N Имя брони
         * @param T Тип брони
         */
        explicit Equipment(name_equipment N, type_equipment T) noexcept;
        /*!
         * @brief Геттер имени брони
         * @return Имя брони
         */
        name_equipment getEquipment_Name() const noexcept { return equipment_name; }
        /*!
         * @brief Геттер типа брони
         * @return Тип брони
         */
        type_equipment getEquipment_Type() const noexcept { return equipment_type; }
        /*!
         * @brief Геттер минимальной защиты
         * @return Минимальная защита
         */
        int getMin_Protect() const noexcept {return min_protect; }
        /*!
         * @brief Геттер максимальной защиты
         * @return Максиамльная защита
         */
        int getMax_Protect() const noexcept {return max_protect; }

        /*!
         * @brief Сеттер имени брони и типа
         * @param N Имя брони
         * @param T Тип брони
         * @return Ссылка на текущую броню
         */
        Equipment& setNameType(name_equipment N, type_equipment T) noexcept;
        /*!
         * @brief Оператор копирования
         * @param I Другая броня
         * @return Ссылка на текущую броню
         */
        Equipment& operator=(const Equipment& I) noexcept;

        /*!
         * @brief Виртуальнйы метод - получить текущую защиту
         */
        virtual int getProtect() const noexcept;
        /*!
         * @brief Виртуальнйы метод - надеть броню на героя
         * @param Карта
         */
        void use(Dungeon &Dungeon) override;

};

#endif // EQUIPMENT_H
