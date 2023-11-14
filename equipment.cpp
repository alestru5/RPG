#include "equipment.h"
#include "game.h"
#include "hero.h"

Equipment::Equipment(name_equipment N, type_equipment T) noexcept: Item(type_item::equipment){
    try{
        equipment_name = N;
        equipment_type = T;
        min_protect = SetProtect::createProtect(N, T).first;
        max_protect = SetProtect::createProtect(N, T).second;
    } catch(...){
        throw;
    }
}


Equipment& Equipment::setNameType(name_equipment N, type_equipment T) noexcept{
    try{
        equipment_name = N;
        equipment_type = T;
        min_protect = SetProtect::createProtect(N, T).first;
        max_protect = SetProtect::createProtect(N, T).second;
    } catch(...){
        throw;
    }
    return *this;
}

Equipment& Equipment::operator=(const Equipment& I) noexcept{
    if (this != &I){
        equipment_name = I.equipment_name;
        equipment_type = I.equipment_type;
        min_protect = I.min_protect;
        max_protect = I.max_protect;

        Item::operator=(I);
    }
    return *this;
}

int Equipment::getProtect() const noexcept{
    return rand() % (max_protect - min_protect) + min_protect;
}

Item* Equipment::take(Hero *H){
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
    } else if (tmp->getItem_Type() == type_item::equipment_artifact){
        static_cast<EquipmentArtifact*>(tmp)->unUseChanges(H);
    }
    H->setEquipment(L);

    return tmp;
}
