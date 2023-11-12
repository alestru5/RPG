#include "equipmentartifact.h"
#include "hero.h"

EquipmentArtifact::EquipmentArtifact(name_equipment N, type_equipment T, type_artifact A): Equipment(N, T), Artifact(A){
    try{
        bonus_protect = SetProtect::setBonus_Protect(A);
        setType(type_item::equipment_artifact);
    } catch(...){
        throw;
    }

}

int EquipmentArtifact::getProtect() const noexcept{
    return rand() % (max_protect - min_protect) + min_protect + bonus_protect;
}

Item* EquipmentArtifact::take(Hero *H){
    Item * tmp = nullptr;
    std::list<Equipment *> L;
    std::list<Equipment *> T = H->getEquipment();
    for (auto iter = T.begin(); iter != T.end(); iter++){
        if ((*iter)->getEquipment_Type() == equipment_type){
            L.push_back(this);
            tmp = (*iter);
        } else{
            L.push_back(*iter);
        }
    }
    if (tmp == nullptr){
        L.push_back(this);
    }
    H->setEquipment(L);
    return tmp;
}

EquipmentArtifact& EquipmentArtifact::operator=(const EquipmentArtifact& I) noexcept{
    if (this != &I){
        bonus_protect = I.bonus_protect;

        Artifact::operator=(I);
        Equipment::operator=(I);
    }
    return *this;
}
