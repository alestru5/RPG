#include "weapon.h"
#include "game.h"
#include "setdamage.h"

Weapon::Weapon(name_weapon n) noexcept: Item(type_item::weapon) {
    min_damage = SetDamage::createDamage(n).first;
    max_damage = SetDamage::createDamage(n).second;
    weapon_name = n;
}

Weapon& Weapon::setName(name_weapon n) noexcept{
    min_damage = SetDamage::createDamage(n).first;
    max_damage = SetDamage::createDamage(n).second;
    weapon_name = n;
    return *this;
}

Weapon& Weapon::operator=(const Weapon& I) noexcept{
    if (this != &I){
        weapon_name = I.weapon_name;
        min_damage = I.min_damage;
        max_damage = I.max_damage;

        Item::operator=(I);
    }
    return *this;
}

int Weapon::getDamage(Enemy *enemy) const noexcept{
    return rand() % (max_damage - min_damage) + min_damage;
}

void Weapon::use(Dungeon &dungeon){
    Item *tmp = dungeon.getHero().getWeapon();
    if (tmp != nullptr){
        if (tmp->getItem_Type() == type_item::weapon_artifact){
            dynamic_cast<WeaponArtifact *>(tmp)->unUseChanges(dungeon.getHero());
        }
        if (tmp->getItem_Type() == type_item::weapon_artifact_enchantment){
            dynamic_cast<WeaponArtifactEnchantment *>(tmp)->unUseChanges(dungeon.getHero());
        }
    }
    dungeon.getHero().setWeapon(this);
    std::vector<Item *> I = dungeon.getHero().getInventory();
    I[dungeon.getHero().getCurr_Chosen_Item()] = tmp;
    dungeon.getHero().setInventory(I);
}
