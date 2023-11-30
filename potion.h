#ifndef POTION_H
#define POTION_H

#include <list>
#include "table.h"
#include "item.h"
#include "enums.h"
#include "setpotion.h"
/*!
 * @brief Класс зелья
 */
class Potion: public Item{
    private:
        // Название зелья
        name_potion potion_name;
        // Изменения характеристик после употребления
        std::pair<changes_characteristic, int> changes;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Potion() noexcept: changes(), Item(type_item::potion){}
        /*!
         * @brief Конструктор по значению
         * @param N Название зелья
         */
        Potion(name_potion N) noexcept;
        /*!
         * @brief Геттер имени зелья
         * @return Имя зелья
         */
        name_potion getPotion_Name() const noexcept { return potion_name; }
        /*!
         * @brief Геттер изменения характеристик
         * @return Изменение характиристик
         */
        std::pair<changes_characteristic, int> getChanges() { return changes; }
        /*!
         * @brief Оператор копирования
         * @param I Другое зелье
         * @return Ссылка на текущее зелье
         */
        Potion &operator =(const Potion &I) noexcept;
        /*!
         * @brief Виртуальнйы метод - выпить зелье
         * @param Карта
         */
        void use(Dungeon &dungeon) override;
};

#endif // POTION_H
