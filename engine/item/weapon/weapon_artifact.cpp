#include "weapon_artifact.h"

int WeaponArtifact::getValue() const noexcept{
    return rand() % (getMax_Damage() - getMin_Damage()) + bonus_damage;
}

void WeaponArtifact::use(Dungeon &dungeon){
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

Item* WeaponArtifact::buildItem(const json& data) {
    WeaponArtifact *tmp = new WeaponArtifact();
    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->weapon_name = data.at("item_name").get<std::string>();
    std::string a_t = data.at("artifact_type").get<std::string>();
    int ch = data.at("changes").get<int>();
    tmp->setAll(a_t, ch);
    tmp->bonus_damage = data.at("bonus_damage").get<int>();
    tmp->min_damage = data.at("min_damage").get<int>();
    tmp->max_damage = data.at("max_damage").get<int>();
    return tmp;
}

Item* load_weapon_artifact(){
    return new WeaponArtifact();
}
