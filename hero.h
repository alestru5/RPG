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
        int level;

        Weapon *weapon;
        std::list<Equipment*> equipment;

        int curr_chosen_item;
        static const int m_inventory = 10;
        std::vector<Item*> inventory;

        int c_bunch;
        int cur_endurance;

        Table table;

    public:
        Hero();
        Hero(int i, int j);
        Hero(const Hero &H);

        ~Hero() { delete weapon; }

        int getLevel() const noexcept { return level; }
        Weapon* getWeapon() const noexcept { return weapon; }
        std::list<Equipment*> getEquipment() const noexcept { return equipment; }
        int getCurr_Chosen_Item() const noexcept { return curr_chosen_item; }
        int getM_Inventory() const noexcept { return m_inventory; }
        std::vector<Item*> getInventory() const noexcept { return inventory; }
        int getC_Bunch() const noexcept { return c_bunch; }
        int getCur_Endurance() const noexcept { return cur_endurance; }
        Table& getTable() noexcept { return table; }


        Hero &setLevel(int l);
        Hero &setWeapon(Weapon *W) { weapon = W; return *this; }
        Hero &setEquipment(std::list<Equipment*> &E);
        Hero &setCurr_Chosen_Item(int a);
        Hero &setInventory(std::vector<Item*> &I) { inventory = I; return *this; }
        Hero &setC_Bunch(int b);
        Hero &setCur_Endurance(int a);
        Hero &setTable(Table &T) { table = T; return *this; }

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
        void updateHp() noexcept;

        std::string status(Dungeon &dungeon) const noexcept;

        int act(std::string key, Dungeon &dungeon);

        void levelUp(short_characteristic n);
        void drinkPotion();
        void attack(Character *C) override;
        bool take(Dungeon &dungeon);
        void move(type_destination direction, Dungeon &dungeon) override;
        bool open_chest(Dungeon &dungeon) noexcept;
        bool climb(Dungeon &dungeon) noexcept;
        bool change_door(Dungeon &dungeon) noexcept;

};
#endif // HERO_H
