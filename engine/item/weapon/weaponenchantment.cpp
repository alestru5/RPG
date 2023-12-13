#include "weaponenchantment.h"
#include "../../character/hero/hero.h"
#include "../../item/weapon/weaponartifactenchantment.h"
#include "../../dungeon/dungeon.h"

int WeaponEnchantment::getValue() const noexcept{
    return static_cast<int> ((static_cast<double>(rand() % (getMax_Damage() - getMin_Damage()) + getMin_Damage())));
}

void WeaponEnchantment::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    dungeon.getHero().setWeapon(this);
    if (tmp != nullptr){
        if (tmp->getItemType().find("artifact") != std::string::npos){
            dynamic_cast<Artifact *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}
