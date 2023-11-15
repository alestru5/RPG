#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "item.h"
#include "artifact.h"
#include "setprotect.h"

class Equipment: public Item{
    protected:
        name_equipment equipment_name;
        type_equipment equipment_type;
        int min_protect;
        int max_protect;
    public:
        Equipment() noexcept: min_protect(0), max_protect(0), Item(type_item::equipment) {}
        explicit Equipment(name_equipment N, type_equipment T) noexcept;

        virtual ~Equipment() {}

        name_equipment getEquipment_Name() const noexcept { return equipment_name; }
        type_equipment getEquipment_Type() const noexcept { return equipment_type; }
        int getMin_Protect() const noexcept {return min_protect; }
        int getMax_Protect() const noexcept {return max_protect; }

        Equipment& setNameType(name_equipment N, type_equipment T) noexcept;
        Equipment& operator=(const Equipment& I) noexcept;

        virtual int getProtect() const noexcept;

        void use(Dungeon &Dungeon) override;

};

#endif // EQUIPMENT_H
