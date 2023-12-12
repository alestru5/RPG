#ifndef BUNCH_H
#define BUNCH_H

#include <iostream>

#include "../item.h"
#include "../../helps/enums.h"
#include "../../helps/sets/setcount.h"
/*!
 * @brief Класс набора отмычек
 */
class Bunch: public Item{
    private:
        // Тип набора отмычек
        type_bunch bunch_type;
        // Количество отмычек в наборе
        int count;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Bunch() noexcept: count(0), Item(type_item::bunch) {}
        /*!
         * @brief Конструктор по значению
         * @param T Тип набора отмычек
         */
        Bunch(type_bunch T) noexcept;
        /*!
         * @brief Геттер типа набора отмычек
         * @return Тип набора отычек
         */
        type_bunch getBunch_Type() const noexcept { return bunch_type; }
        /*!
         * @brief Геттер кооличества отмычек
         * @return Количество отмычек
         */
        int getCount() const noexcept { return count; }
        /*!
         * @brief Оператор копирования
         * @param I Другой набор отмычек
         * @return Ссылка на текущий набор отмычек
         */
        Bunch &operator= (const Bunch &I) noexcept;
        /*!
         * @brief Виртуальнйы метод - распаковать набор отмычек и положить в "карман"
         * @param Карта
         */
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}

};

#endif // BUNCH_H
