#include "weaponartifactenchantment.h"
#include "hero.h"
#include "dungeon.h"

int WeaponArtifactEnchantment::getDamage(Enemy *enemy) const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())) * getMultiply(enemy));
}

void WeaponArtifactEnchantment::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr && (tmp->getItem_Type() == type_item::weapon_artifact || tmp->getItem_Type() == type_item::weapon_artifact_enchantment)){
        if (tmp->getItem_Type() == type_item::weapon_artifact){
            dynamic_cast<WeaponArtifact *>(tmp)->unUseChanges(dungeon.getHero());
        } else{
            dynamic_cast<WeaponArtifactEnchantment *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    useChanges(dungeon.getHero());
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}
