#ifndef HERO_H
#define HERO_H

#include <list>

#include "character.h"
#include "weapon.h"
#include "equipment.h"
#include "potion.h"
#include "table.h"
#include "enums.h"
#include "enumtostring.h"
#include "enemy.h"

class Hero : public Character {
    private:
        Weapon *weapon;
        std::list<Equipment*> equipment;

        int curr_chosen_item;
        static const int m_inventory = 10;
        std::vector<Item*> inventory;

        int c_bunch;
        int cur_endurance;

        Table table;

        void updateHp() noexcept;
    public:
        Hero() noexcept;
        Hero(int i, int j) noexcept;
        Hero(const Hero &H) noexcept;

        ~Hero() { delete weapon; }

        Weapon* getWeapon() const noexcept { return weapon; }
        std::list<Equipment*> getEquipment() const noexcept { return equipment; }
        int getCurr_Chosen_Item() const noexcept { return curr_chosen_item; }
        Item *getCurrChosenItem() noexcept { return inventory[curr_chosen_item]; }
        int getM_Inventory() const noexcept { return m_inventory; }
        std::vector<Item*> getInventory() const noexcept { return inventory; }
        int getC_Bunch() const noexcept { return c_bunch; }
        int getCur_Endurance() const noexcept { return cur_endurance; }
        Table& getTable() noexcept { return table; }


        Hero &setLevel(int l);
        Hero &setWeapon(Weapon *W) noexcept { weapon = W; return *this; }
        Hero &setEquipment(std::list<Equipment*> &E) noexcept;
        Hero &setCurr_Chosen_Item(int a);
        Hero &setInventory(std::vector<Item*> &I) noexcept { inventory = I; return *this; }
        Hero &setC_Bunch(int b);
        Hero &setCur_Endurance(int a);
        Hero &setTable(Table &T) noexcept { table = T; return *this; }

        Hero& operator=(const Hero& H);

        void nextChosenItem() noexcept { curr_chosen_item = (curr_chosen_item + 1) % m_inventory;}
        int fullProtect() const noexcept;
        int minProtect() const noexcept;
        int maxProtect() const noexcept;
        int minDamage() const noexcept;
        int maxDamage() const noexcept;
        void getDamage(int damage) override;

        int findEnemy(Dungeon &dungeon) const noexcept;
        int fullDamage(Enemy *enemy) const noexcept;
        void updateEndurance() noexcept;

        void addExperience(int a);
        void levelUp(short_characteristic n);
        void usingChosenItem(Dungeon &dungeon) noexcept;
        void attack(Character *C) override;
        bool take(Dungeon &dungeon);
        void move(type_destination direction, Dungeon &dungeon) noexcept override;
        bool open_chest(Dungeon &dungeon) noexcept;
        bool climb(Dungeon &dungeon) noexcept;
        bool change_door(Dungeon &dungeon) noexcept;

};
#endif // HERO_H
