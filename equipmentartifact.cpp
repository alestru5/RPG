#include "equipmentartifact.h"

EquipmentArtifact::EquipmentArtifact(name_equipment N, type_equipment T, type_artifact A): Equipment(N, T), Artifact(A){
    try{
        bonus_protect = SetProtect::setBonus_Protect(A);
        setType(type_item::equipment_artifact);
    } catch(...){
        throw;
    }

}

EquipmentArtifact& EquipmentArtifact::operator=(const EquipmentArtifact& I) noexcept{
    if (this != &I){
        bonus_protect = I.bonus_protect;

        Artifact::operator=(I);
        Equipment::operator=(I);
    }
    return *this;
}
