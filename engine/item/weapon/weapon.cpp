#include "weapon.h"


Weapon& Weapon::operator=(const Weapon& I) noexcept{
    if (this != &I){
        item_type = I.item_type;
        weapon_name = I.weapon_name;
        min_damage = I.min_damage;
        max_damage = I.max_damage;

        Item::operator=(I);
    }
    return *this;
}

int Weapon::getValue() const noexcept{
    return rand() % (max_damage - min_damage) + min_damage;
}

void Weapon::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    if (tmp != nullptr){
        if (tmp->getItemType().find("artifact") != std::string::npos){
            dynamic_cast<Artifact *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    dungeon.getHero().setWeapon(this);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

Item* Weapon::buildItem(const json& data) {
    Weapon *tmp = new Weapon();
    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->weapon_name = data.at("item_name").get<std::string>();
    tmp->min_damage = data.at("min_damage").get<int>();
    tmp->max_damage = data.at("max_damage").get<int>();
    return tmp;
}

Item* load_weapon(){
    return new Weapon();
}