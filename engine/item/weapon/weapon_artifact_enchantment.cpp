#include "weapon_artifact_enchantment.h"


int WeaponArtifactEnchantment::getValue() const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())));
}

void WeaponArtifactEnchantment::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr && (tmp->getItemType().find("artifact") != std::string::npos)){
        dynamic_cast<Artifact *>(tmp)->unUseChanges(dungeon.getHero());
    }
    useChanges(dungeon.getHero());
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

Item* WeaponArtifactEnchantment::buildItem(const json& data) {
    WeaponArtifactEnchantment *tmp = new WeaponArtifactEnchantment();
    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->weapon_name = data.at("item_name").get<std::string>();
    std::string e_t = data.at("enchantment_type").get<std::string>();
    int cf = data.at("coef").get<int>();
    tmp->setAllC(e_t, cf);
    std::string a_t = data.at("artifact_type").get<std::string>();
    int ch = data.at("changes").get<int>();
    tmp->setAll(a_t, ch);
    tmp->bonus_damage = data.at("bonus_damage").get<int>();
    tmp->min_damage = data.at("min_damage").get<int>();
    tmp->max_damage = data.at("max_damage").get<int>();
    return tmp;
}

Item* load_weapon_artifact_enchantment(){
    return new WeaponArtifactEnchantment();
}