#ifndef SETITEM_H
#define SETITEM_H
#include "item.h"
#include "enums.h"
#include "equipment.h"
#include "equipmentartifact.h"
#include "weaponartifactenchantment.h"
#include "potion.h"
#include "bunch.h"
class SetItem{
    public:
        static Item *createItem();
};

#endif // SETITEM_H
