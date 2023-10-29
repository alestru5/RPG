#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include<string>



class Dungeon;

class Character{
    protected:
        int experience;
        int max_hp;
        int cur_hp;
        int x;
        int y;
    public:
        Character(): experience(0), max_hp(100), cur_hp(100), x(14), y(1) {}
        Character(int e, int m, int c, int x, int y);

        void setX(int i);
        void setY(int j);
        void setExperience(int exp);
        void setMax_Hp(int hp);
        void setCur_Hp(int hp);

        int getX() const noexcept {return x; }
        int getY() const noexcept {return y; }
        int getExperience() const noexcept { return experience; }
        int getMax_Hp() const noexcept { return max_hp; }
        int getCur_Hp() const noexcept { return cur_hp; }





};

#endif // CHARACTER_H
