#ifndef ITEM_H
#define ITEM_H


#include "../../json.hpp"
#include "../dungeon/dungeon.h"
using json = nlohmann::json;

#include "../helps/enums.h"
/*!
 * @brief Расширяемый класс - предмет
 */
class Item{
public:
    /*!
     * @brief Получить тип предмета
     * @return std::string
     */
    virtual std::string getItemType() const noexcept = 0;
    /*!
     * @brief Получить название предмета
     * @return std::string
     */
    virtual std::string getItemName() const noexcept = 0;
    /*!
     * @brief Получить значение предмета
     * @return int
     */
    virtual int getValue() const noexcept = 0;
    /*!
     * @brief Использовать предмет.
     * @brief Броня - надеть
     * @brief Оружие - взять в руки
     * @brief Зелье - выпить
     * @brief Отмыки - распаковать
     * @brief Кирка - сломать стену
     * @return std::string
     */
    virtual void use(Dungeon &dungeon) = 0;
    virtual Item* buildItem(const json& data) = 0;
    virtual ~Item() = default;

};

#endif // ITEM_H
