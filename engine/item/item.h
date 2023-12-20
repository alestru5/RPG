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
    virtual std::string getItemType() const noexcept = 0;
    virtual std::string getItemName() const noexcept = 0;
    virtual int getValue() const noexcept = 0;
    virtual void use(Dungeon &dungeon) = 0;
    virtual Item& buildItem(const json& data) = 0;

};

#endif // ITEM_H
