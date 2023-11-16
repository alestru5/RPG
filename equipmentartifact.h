#ifndef EQUIPMENTARTIFACT_H
#define EQUIPMENTARTIFACT_H

#include "equipment.h"

class EquipmentArtifact: public Equipment, public Artifact{
    private:
        int bonus_protect;

    public:
        EquipmentArtifact() noexcept: Equipment(), Artifact(), bonus_protect(0) { setType(type_item::equipment_artifact); }
        EquipmentArtifact(name_equipment N, type_equipment T, type_artifact A) noexcept;

        ~EquipmentArtifact() {}

        int getProtect() const noexcept override;

        void use(Dungeon &dungeon) override;

        EquipmentArtifact& operator=(const EquipmentArtifact& I) noexcept;
};

#endif // EQUIPMENTARTIFACT_H
