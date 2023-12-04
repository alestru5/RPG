#ifndef ITEM_H
#define ITEM_H

#include "../helps/enums.h"

class Hero;
class Dungeon;
/*!
 * @brief Расширяемый класс - предмет
 */
class Item{
    private:
        //Тип предмета
        type_item item_type;
    public:
        /*!
         * @brief Конструктор по значению
         * @param T Тип предмета
         */
        Item(type_item T) noexcept: item_type(T) {}

        /*!
         * @brief Геттер типа предмета
         * @return T Тип предмета
         */
        type_item getItem_Type() const noexcept { return item_type; }
        /*!
         * @brief Сеттер типа предмета
         * @param T Тип предмета
         */
        void setType(type_item T) noexcept { item_type = T; }
        /*!
         * @brief Оператор копирования
         * @param I Копируемый предмет
         */
        Item& operator =(const Item& I) noexcept;
        /*!
         * @brief Чисто виртуальный метод использования предмета
         * @note Использовать броню - надеть
         * @note Использовать отмычку - положить в "карман"
         * @note Использовать оружие - взять в руки
         * @note Использовать зелье - выпить
         * @param dungeon Карта
         * @return Ссылка на этот предмет
         */
        virtual void use(Dungeon &dungeon) = 0;


};

#endif // ITEM_H
