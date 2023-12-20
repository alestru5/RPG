#include "equipment_artifact.h"
#include "../../dungeon/dungeon.h"

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

const Item& load_equipment_artifact(){
    static EquipmentArtifact pluginInst;
    return pluginInst;
}