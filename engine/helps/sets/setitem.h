#ifndef SETITEM_H
#define SETITEM_H

#include "../../item/item.h"
#include "../enums.h"
#include "../../item/equipment/equipment.h"
#include "../../item/equipment/equipmentartifact.h"
#include "../../item/weapon/weaponartifactenchantment.h"
#include "../../item/potion/potion.h"
#include "../../item/bunch/bunch.h"

class SetItem{
    public:
        static Item *createItem();
};

#endif // SETITEM_H
