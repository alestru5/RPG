#ifndef PICKAXE_H
#define PICKAXE_H

#include <iostream>

#include "../item.h"
/*!
 * @brief Класс кирки
 */
class Pickaxe: public Item{
    private:
        
        std::string item_type;
        std::string pickaxe_name;
        int durability;

    public:

        Pickaxe() noexcept: durability(0), item_type("pickaxe"), pickaxe_name("broken"){}
        Pickaxe(std::string name, int c) noexcept;

        Pickaxe &operator= (const Pickaxe &I) noexcept;

        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return pickaxe_name; }
        int getValue() const noexcept override { return durability; }
        void use(Dungeon &dungeon) override;
        Item* buildItem(const json& data) override;

};
extern "C" Item* load_pickaxe() {
    return new Pickaxe();
}
#endif // PICKAXE_H
