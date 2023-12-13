#include "weaponartifact.h"
#include "../../character/hero/hero.h"
#include "../../item/weapon/weaponartifactenchantment.h"
#include "../../dungeon/dungeon.h"

int WeaponArtifact::getValue() const noexcept{
    return rand() % (getMax_Damage() - getMin_Damage()) + bonus_damage;
}

void WeaponArtifact::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr && (tmp->getItemType().find("artifact") != std::string::npos)){
            dynamic_cast<Artifact *>(tmp)->unUseChanges(dungeon.getHero());
    }
    useChanges(dungeon.getHero());
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}

