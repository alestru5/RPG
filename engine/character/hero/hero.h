#ifndef HERO_H
#define HERO_H

#include <list>

#include "../character.h"
#include "../../item/weapon/weapon.h"
#include "../../item/equipment/equipment.h"
#include "../../item/potion/potion.h"
#include "../../upgrades/table/table.h"
#include "../../helps/enums.h"
#include "../../helps/enumtostring.h"
#include "../../character/enemy/enemy.h"

class Hero : public Character {
    private:
        Item *weapon;
        std::list<Item*> equipment;

        int curr_chosen_item;
        static const int m_inventory = 10;
        std::vector<Item*> inventory;

        int c_bunch;
        int protect;
        int cur_endurance;

        Table table;

        void updateHp() noexcept;
    public:
        Hero() noexcept;
        Hero(int i, int j) noexcept;
        Hero(const Hero &H) noexcept;

        ~Hero() { delete weapon; }

        Item* getWeapon() const noexcept { return weapon; }
        std::list<Item*> getEquipment() const noexcept { return equipment; }
        int getCurr_Chosen_Item() const noexcept { return curr_chosen_item; }
        Item *getCurrChosenItem() noexcept { return inventory[curr_chosen_item]; }
        int getM_Inventory() const noexcept { return m_inventory; }
        std::vector<Item*> getInventory() const noexcept { return inventory; }
        int getC_Bunch() const noexcept { return c_bunch; }
        int getCur_Endurance() const noexcept { return cur_endurance; }
        Table& getTable() noexcept { return table; }


        Hero &setWeapon(Item *W) noexcept { weapon = W; return *this; }
        Hero &setEquipment(std::list<Item*> &E) noexcept;
        Hero &setCurr_Chosen_Item(int a);
        Hero &setInventory(std::vector<Item*> &I) noexcept { inventory = I; return *this; }
        Hero &setC_Bunch(int b);
        Hero &setCur_Endurance(int a);
        Hero &setTable(Table &T) noexcept { table = T; return *this; }

        Hero& operator=(const Hero& H);

        void nextChosenItem() noexcept { curr_chosen_item = (curr_chosen_item + 1) % m_inventory;}
        void prevChosenItem() noexcept;
        int fullProtect() const noexcept;
        int minProtect() const noexcept;
        int maxProtect() const noexcept;
        int minDamage() const noexcept;
        int maxDamage() const noexcept;
        void getDamage(int damage) override;

        int findEnemy(Dungeon &dungeon) const noexcept;
        int findEnemy(Dungeon &dungeon, int k, int l) const noexcept;
        int fullDamage(Enemy *enemy) const noexcept;

        void addExperience(int a);
        void levelUp(std::string n);
        void usingChosenItem(Dungeon &dungeon) noexcept;
        void attack(Character *C) override;
        bool take(Dungeon &dungeon);
        void move(type_destination direction, Dungeon &dungeon) noexcept override;
        bool open_chest(Dungeon &dungeon) noexcept;
        bool climb(Dungeon &dungeon) noexcept;
        bool change_door(Dungeon &dungeon) noexcept;

};
#endif // HERO_H
