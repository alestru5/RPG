#include "equipment.h"
#include "game.h"

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
}
/*int Equipment::final_protect() const noexcept{
    int protect = min_protect + rand() % (max_protect - min_protect);
    damage += Game::dungeon.getHero().getTable().getValue(short_characteristic::agility) / 2;
    return protect;
}*/

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
