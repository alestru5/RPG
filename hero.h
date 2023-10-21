#ifndef HERO_H
#define HERO_H
#include "character.h"

struct characteristic{
    int max_hp;
    int current_hp;
    int strength;
    int agility;
    int intelligence;
    int endurance;
    characteristic(int mh, int ch, int s, int a, int i, int e): max_hp(mh), current_hp(ch), strength(s), agility(a), intelligence(i), endurance(e){};
};

class Hero : public Character {
    private:
        int level;
        int experience;
        struct characteristic characteristic;
        /* оружие, список снаряжения, зелья*/
    public:
        Hero();
        Hero(int i, int j);
        Hero operator=(const Hero& H);
        int act(std::string key);
        int getX() {return x; }
        int getY() {return y; }


};
#endif // HERO_H
