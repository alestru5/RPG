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
        std::string item_type;
        std::string bunch_name;
        // Количество отмычек в наборе
        int count;

    public:
        /*!
         * @brief Пустой конструктор
         */
        Bunch() noexcept: count(0), item_type("bunch"){}
        Bunch(std::string name, int c) noexcept: bunch_name(name), count(c), item_type("bunch") {}

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

        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return bunch_name; }
        int getValue() const noexcept override { return count; }
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}

};
extern "C" const Item& load_bunch() {
    static Bunch pluginInst;
    return pluginInst;
}
#endif // BUNCH_H
