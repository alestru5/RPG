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

class Hero : public Character {
    private:
        int level;

        Weapon *weapon;
        std::list<Equipment*> equipment;
        int m_potion;
        std::list<Potion*> potion;
        int c_bunch;

        Table table;

    public:
        Hero();
        Hero(int i, int j);
        Hero(const Hero &H);

        ~Hero() {}

        int getLevel() const noexcept { return level; }
        Weapon* getWeapon() const noexcept { return weapon; }
        std::list<Equipment*> getEquipment() const noexcept { return equipment; }
        int getM_Potion() const noexcept { return m_potion; }
        std::list<Potion*> getPotion() const noexcept { return potion; }
        int getC_Bunch() const noexcept { return c_bunch; }
        Table getTable() const noexcept { return table; }


        Hero &setLevel(int l);
        Hero &setWeapon(Weapon *W) { weapon = W; return *this; }
        Hero &setEquipment(std::list<Equipment*> &E);
        Hero &setM_Potion(int m);
        Hero &setPotion(std::list<Potion*> &P) { potion = P; return *this; }
        Hero &setC_Bunch(int b);
        Hero &setTable(Table &T) { table = T; return *this; }

        Hero& operator=(const Hero& H);

        //Hero &drinkPotion(Potion *P);
        //Hero &upLevel();

        int fullProtect() const noexcept;
        int minProtect() const noexcept;
        int maxProtect() const noexcept;
        void getDamage(int damage);
        bool isDead() const noexcept { return cur_hp <= 0; }

        std::string status() const noexcept;

        int act(std::string key);

        bool take();
        bool move(std::string direction);
        bool open_chest() noexcept;
        bool climb() noexcept;
        bool change_door() noexcept;

};
#endif // HERO_H
