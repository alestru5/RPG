#include "equipment.h"

Equipment& Equipment::operator=(const Equipment& I) noexcept{
    if (this != &I){
        item_type = I.item_type;
        equipment_name = I.equipment_name;
        equipment_type = I.equipment_type;
        min_protect = I.min_protect;
        max_protect = I.max_protect;
    }
    return *this;
}

int Equipment::getValue() const noexcept{
    return rand() % (max_protect - min_protect) + min_protect;
}

void Equipment::use(Dungeon &dungeon){
    Item * tmp = nullptr;
    std::list<Item *> L;
    std::list<Item *> T = dungeon.getHero().getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        if (static_cast<Equipment*>(*iter)->getEquipment_Type() == equipment_type){
            L.push_back(this);
            tmp = (*iter);
        } else{
            L.push_back(*iter);
        }
    }
    if (tmp == nullptr){
        L.push_back(this);
    } else if (tmp->getItemType().find("artifact") != std::string::npos){
        dynamic_cast<Artifact*>(tmp)->unUseChanges(dungeon.getHero());
    }
    dungeon.getHero().setEquipment(L);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

Item& Equipment::buildItem(const json& data) {
    item_type = data.at("item_type").get<std::string>();
    equipment_name = data.at("item_name").get<std::string>();
    equipment_type = data.at("equipment_type").get<std::string>();
    min_protect = data.at("min_protect").get<int>();
    max_protect = data.at("max_protect").get<int>();
    return *this;
}

const Item& load_equipment(){
    static Equipment pluginInst;
    return pluginInst;
}
