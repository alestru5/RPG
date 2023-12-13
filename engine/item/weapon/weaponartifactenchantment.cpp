#include "weaponartifactenchantment.h"
#include "../../character/hero/hero.h"
#include "../../dungeon/dungeon.h"


int WeaponArtifactEnchantment::getValue() const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())));
}

void WeaponArtifactEnchantment::use(Dungeon &dungeon){
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
