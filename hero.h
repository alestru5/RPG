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
        int m_potion;
        std::list<Potion*> potion;
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
        int getM_Potion() const noexcept { return m_potion; }
        std::list<Potion*> getPotion() const noexcept { return potion; }
        int getC_Bunch() const noexcept { return c_bunch; }
        Table& getTable() noexcept { return table; }


        Hero &setLevel(int l);
        Hero &setWeapon(Weapon *W) { weapon = W; return *this; }
        Hero &setEquipment(std::list<Equipment*> &E);
        Hero &setM_Potion(int m);
        Hero &setPotion(std::list<Potion*> &P) { potion = P; return *this; }
        Hero &setC_Bunch(int b);
        Hero &setTable(Table &T) { table = T; return *this; }

        Hero& operator=(const Hero& H);

        //Hero &upLevel();
        void changeOrderPotion() noexcept;
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

        void drinkPotion();
        void attack(Character *C) override;
        bool take(Dungeon &dungeon);
        void move(type_destination direction, Dungeon &dungeon) override;
        bool open_chest(Dungeon &dungeon) noexcept;
        bool climb(Dungeon &dungeon) noexcept;
        bool change_door(Dungeon &dungeon) noexcept;

};
#endif // HERO_H
