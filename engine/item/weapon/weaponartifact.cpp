#include "weaponartifact.h"
#include "../../character/hero/hero.h"
#include "../../item/weapon/weaponartifactenchantment.h"
#include "../../dungeon/dungeon.h"

WeaponArtifact::WeaponArtifact(name_weapon N, type_artifact T) noexcept: Weapon(N), Artifact(T){
    bonus_damage = SetDamage::setBonus_Damage(T);
    setType(type_item::weapon_artifact);
}


int WeaponArtifact::getDamage(Enemy *enemy) const noexcept{
    return rand() % (getMax_Damage() - getMin_Damage()) + bonus_damage;
}

void WeaponArtifact::use(Dungeon &dungeon){
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

