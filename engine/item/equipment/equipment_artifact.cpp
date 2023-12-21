#include "equipment_artifact.h"

int EquipmentArtifact::getValue() const noexcept{
    return rand() % (max_protect - min_protect) + min_protect + bonus_protect;
}

void EquipmentArtifact::use(Dungeon &dungeon){
    Item * tmp = nullptr;
    std::list<Item *> L;
    std::list<Item *> T = dungeon.getHero().getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        if (dynamic_cast<Equipment *>(*iter)->getEquipment_Type() == equipment_type){
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
    useChanges(dungeon.getHero());
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

EquipmentArtifact& EquipmentArtifact::operator=(const EquipmentArtifact& I) noexcept{
    if (this != &I){
        bonus_protect = I.bonus_protect;
        Artifact::operator=(I);
        Equipment::operator=(I);
    }
    return *this;
}

Item* EquipmentArtifact::buildItem(const json& data){
    EquipmentArtifact *tmp = new EquipmentArtifact();

    tmp->item_type = data.at("item_type").get<std::string>();
    tmp->equipment_name = data.at("item_name").get<std::string>();
    tmp->equipment_type = data.at("equipment_type").get<std::string>();
    std::string a_t = data.at("artifact_type").get<std::string>();
    int ch = data.at("changes").get<int>();
    tmp->setAll(a_t, ch);
    tmp->min_protect = data.at("min_protect").get<int>();
    tmp->max_protect = data.at("max_protect").get<int>();
    tmp->bonus_protect = data.at("bonus_protect").get<int>();
    return tmp;
}

Item* load_equipment_artifact(){
    return new EquipmentArtifact();
}