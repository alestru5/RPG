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

void Equipment::use(Dungeon &dungeon){
    Item * tmp = nullptr;
    std::list<Equipment *> L;
    std::list<Equipment *> T = dungeon.getHero().getEquipment();
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
        static_cast<EquipmentArtifact*>(tmp)->unUseChanges(dungeon.getHero());
    }
    dungeon.getHero().setEquipment(L);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}
