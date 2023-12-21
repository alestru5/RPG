#include "weapon_enchantment.h"

int WeaponEnchantment::getValue() const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())));
}

void WeaponEnchantment::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr){
        if (tmp->getItemType().find("artifact") != std::string::npos){
            dynamic_cast<Artifact *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

Item* WeaponEnchantment::buildItem(const json& data) {
    WeaponEnchantment *tmp = new WeaponEnchantment();
    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->weapon_name = data.at("item_name").get<std::string>();
    std::string e_t = data.at("enchantment_type").get<std::string>();
    int c = data.at("coef").get<int>();
    tmp->setAllC(e_t, c);
    tmp->min_damage = data.at("min_damage").get<int>();
    tmp->max_damage = data.at("max_damage").get<int>();
    return tmp;
}

Item* load_weapon_enchantment(){
    return new WeaponEnchantment();
}