#include "pickaxe.h"

Pickaxe::Pickaxe(std::string name, int c) noexcept: pickaxe_name(name), item_type("pickaxe") {
    if (c < 0){
        throw std::invalid_argument("negative value");
    }
    durability = c;
}

Pickaxe& Pickaxe::operator= (const Pickaxe &I) noexcept{
    if (this != &I){
        pickaxe_name = I.pickaxe_name;
        durability = I.durability;
    }
    return *this;
}

void Pickaxe::use(Dungeon &dungeon){
    if (durability <= 0){
        return;
    }
    int x = dungeon.getHero().getX();
    int y = dungeon.getHero().getY();
    auto it = dungeon.getCurLevel().beginS(
        [&](Cell C, int index){
            return C.isWall() && ((std::abs(index % dungeon.getCurLevel().getN() - y) == 1 && std::abs(index / dungeon.getCurLevel().getN() - x) == 0) ||
                                  (std::abs(index % dungeon.getCurLevel().getN() - y) == 0 && std::abs(index / dungeon.getCurLevel().getN() - x) == 1));
        });
    if (it == dungeon.getCurLevel().endS()){
        return;
    }
    (*it).setType(type_cell::floor);
    if (durability == 1){
        std::vector<Item *> I = dungeon.getHero().getInventory();
        I[dungeon.getHero().getCurr_Chosen_Item()] = nullptr;
        dungeon.getHero().setInventory(I);
    }
    durability -= 1;
}


Item* Pickaxe::buildItem(const json& data) {
    Pickaxe *tmp = new Pickaxe();
    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->pickaxe_name = data.at("item_name").get<std::string>();
    tmp->durability = data.at("durability").get<int>();
    return tmp;
}