#ifndef POTION_H
#define POTION_H

#include <list>
#include "../../upgrades/table/table.h"
#include "../item.h"
#include "../../helps/enums.h"
/*!
 * @brief Класс зелья
 */
class Potion: public Item{
    private:
        // Название зелья
        std::string item_type;
        std::string potion_name;
        // Изменения характеристик после употребления
        std::pair<std::string, int> changes;
    public:
        /*!
         * @brief Пустой конструктор
         */
        Potion() noexcept: item_type("potion"){}
        Potion(std::string pn, std::pair<std::string, int> c) noexcept: potion_name(pn), changes(c), item_type("potion") {}
        /*!
         * @brief Геттер имени зелья
         * @return Имя зелья
         */
        std::string getPotion_Name() const noexcept { return potion_name; }
        /*!
         * @brief Геттер изменения характеристик
         * @return Изменение характиристик
         */
        std::pair<std::string, int> getChanges() { return changes; }
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
        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return potion_name; }
        int getValue() const noexcept override { return changes.second; }
        void use(Dungeon &dungeon) override;
        Item& buildItem(const json& data) override {}
};
extern "C" const Item& load_potion() {
        static Potion pluginInst;
        return pluginInst;
}
#endif // POTION_H
