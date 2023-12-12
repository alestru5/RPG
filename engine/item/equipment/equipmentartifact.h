#ifndef EQUIPMENTARTIFACT_H
#define EQUIPMENTARTIFACT_H

#include "equipment.h"
/*!
 * @brief Класс брони-артифакта
 */
class EquipmentArtifact: public Equipment, public Artifact{
    private:
        // Бонусная броня
        int bonus_protect;

    public:
        /*!
         * @brief Пустой конструктор
         */
        EquipmentArtifact() noexcept: Equipment(), Artifact(), bonus_protect(0) { setType(type_item::equipment_artifact); }
        /*!
         * @brief Конструктор по значению
         * @param N Имя брони
         * @param T Тип брони
         * @param A Тип артифакта
         */
        EquipmentArtifact(name_equipment N, type_equipment T, type_artifact A) noexcept;
        /*!
         * @brief Виртуальнйы метод - получить текущую защиту
         */
        int getProtect() const noexcept override;
        /*!
         * @brief Виртуальнйы метод - надеть броню на героя
         * @param Карта
         */
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}
        /*!
         * @brief Оператор копирования
         * @param I Другая броня
         * @return Ссылка на текущую броню
         */
        EquipmentArtifact& operator=(const EquipmentArtifact& I) noexcept;
};

#endif // EQUIPMENTARTIFACT_H
