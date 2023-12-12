#include "equipmentartifact.h"
#include "../../character/hero/hero.h"
#include "../../dungeon/dungeon.h"

EquipmentArtifact::EquipmentArtifact(name_equipment N, type_equipment T, type_artifact A) noexcept: Equipment(N, T), Artifact(A){
    bonus_protect = SetProtect::setBonus_Protect(A);
    setType(type_item::equipment_artifact);
}

int EquipmentArtifact::getProtect() const noexcept{
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
    } else if (tmp->getItem_Type() == type_item::equipment_artifact){
        static_cast<EquipmentArtifact *>(tmp)->unUseChanges(dungeon.getHero());
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