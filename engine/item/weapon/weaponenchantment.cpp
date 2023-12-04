#include "weaponenchantment.h"
#include "../../character/hero/hero.h"
#include "../../item/weapon/weaponartifactenchantment.h"
#include "../../dungeon/dungeon.h"

int WeaponEnchantment::getDamage(Enemy *enemy) const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())) * getMultiply(enemy));
}

void WeaponEnchantment::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr){
        if (tmp->getItem_Type() == type_item::weapon_artifact){
            dynamic_cast<WeaponArtifact *>(tmp)->unUseChanges(dungeon.getHero());
        }
        if (tmp->getItem_Type() == type_item::weapon_artifact_enchantment){
            dynamic_cast<WeaponArtifactEnchantment *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}
